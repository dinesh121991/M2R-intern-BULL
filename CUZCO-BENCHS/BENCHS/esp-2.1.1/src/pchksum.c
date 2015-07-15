#define _XOPEN_SOURCE 500
/* the above line is to define the type input to usleep */
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#ifdef PE_CHKPT
#include <pm_ckpt.h>
#endif
#include "genrand.h"
#include "sha1.h"


static int p_myrank = -1;
static struct timeval tck = { 0, 0 };
static struct timeval trs = { 0, 0 };
static long long tsub = 0;

#ifdef PE_CHKPT
void p_ck_cb( void )
{
  gettimeofday(&tck, 0);
}

void p_rs_cb( void )
{
  gettimeofday(&trs, 0);
  tsub = (trs.tv_sec - tck.tv_sec)*1000000 + (trs.tv_usec - tck.tv_usec);
  if (p_myrank == 0)
    printf(" Restart TSUB : %lld\n", tsub);
}

void p_rm_cb( void )
{
  gettimeofday(&trs, 0);
  tsub = (trs.tv_sec - tck.tv_sec)*1000000 + (trs.tv_usec - tck.tv_usec);
  if (p_myrank == 0)
    printf(" Resume TSUB : %lld\n", tsub);
}

#endif

long long pdelta_tv_offset( struct timeval tend, struct timeval tstart, struct timeval tckpt, struct timeval trsm )
{
  long long		tdel, xdel;

  xdel = (tend.tv_sec - tstart.tv_sec)*1000000 + (tend.tv_usec - tstart.tv_usec);
  if ((tstart.tv_sec < tckpt.tv_sec) && (tend.tv_sec > trsm.tv_sec)) {
    tdel = (trsm.tv_sec - tckpt.tv_sec )*1000000 + (trsm.tv_usec - tckpt.tv_usec);
    xdel -= (trsm.tv_sec - tckpt.tv_sec )*1000000 + (trsm.tv_usec - tckpt.tv_usec);
  }
  return xdel;
}
  




/*
 *   pchksum
 *
 *   Usage:
 *          -t secs      : requested run time in secs
 *          -T msecs     : requested run time in millisecs
 *          -n loopcount : number of iterations (overrides time requirements)
 *          -E           : toggle throttle (feedback loop to comm. contention)
 *          -u usecs     : sleep time
 *          -v           : toggle verbose
 *
 *
 *   Each task generates a random message string and computes 
 *   a digest.
 *
 *               Z ----> task ----> Y
 *
 *   Each tasks sends the random message to Y and recieves a 
 *   similar message from Z. The rank of Y & Z are randomly-
 *   generated. With each received message, the task does an 
 *   XOR operation onto a message buffer which initially contained
 *   its random message.
 *
 *   Continue this operation until requested time has expired.
 *
 *   The next part, repeats the above operation but in reverse
 *   order of Y & Z ranks. After the last XOR operation, the 
 *   updated message should be exactly the same as the initial 
 *   message. Or, equivalently their digests should match.
 *
 *   Return status if digests match.
 *
 *   This code does not do anything useful (apparently). It
 *   will however stress the communication subsystem and ensure
 *   correctness of the execution. It will also run on an
 *   arbitarily large partition size and for any specified time.
 *   
 */



#define MAX(x,y)		((x > y) ? x : y);
#define BUFFLEN			46543          		/* 64-bit words */
#define MAXREPLAY		1000

#ifdef USE_RUSAGE
#define GET_CLOCK(x)		getrusage(RUSAGE_SELF, &x)
#define MUSESYS(x)              ((x.ru_utime.tv_sec + x.ru_stime.tv_sec)*1000.0+((x.ru_utime.tv_usec + x.ru_stime.tv_usec)/1000.0))
#define USESYS(x)               ((x.ru_utime.tv_sec + x.ru_stime.tv_sec)*1000000+(x.ru_utime.tv_usec + x.ru_stime.tv_usec))
#define DELTA_TV2MSEC(x,y)      (MUSESYS(x) - MUSESYS(y))
#define DELTA_TV2USEC(x,y)      (USESYS(x) - USESYS(y))
#else
#ifdef USE_UTIME
#define GET_CLOCK(x)		x=clock()
#define DELTA_TV2MSEC(x,y)      (((double)(x-y)*1.e+3)/((double)CLOCKS_PER_SEC))
#define DELTA_TV2USEC(x,y)      (((double)(x-y)*1.e+6)/((double)CLOCKS_PER_SEC))
#else
#define GET_CLOCK(x)		x=MPI_Wtime();
#define DELTA_TV2MSEC(x,y)	((x-y)*1000)
#define DELTA_TV2USEC(x,y)	((x-y)*1000*1000)
#endif
#endif

#if DEBUG>1
#define DEFAULT_VERBOSE		DEBUG
#else
#define DEFAULT_VERBOSE		0
#endif

void			gettofrom( int, int [], int []);
void 			XOR_merge( int, uint64_t [], const uint64_t [] );

static unsigned long	svec[GENRAND_VLEN+1];

int main(int argc, char *(argv[]) )
{
  struct tfreplay {
    int		to;
    int		from;
  } 			tfr[MAXREPLAY];
  int			*to, *from;
  int			i, j, k, jj;
  int			jnode, itmp;
  int			loopmax = -1;
  int			verbose = DEFAULT_VERBOSE;
  int			throttle = 1;
  int			buflen, sleep_factor = 4;
  double		maxtime = -1.0;
  int			myrank, nnode, abortflg, nodecntrl;
  uint64_t		*rbuff, *sbuff, *tbuff;
  char			*rbuf0, *sbuf0, *tbuf0;
  unsigned char		*csp, *ctp;
  unsigned int		ttag = 0x77a, aborttag = 0x07;
  unsigned long		*snd_ts, *rcv_ts, *t_ts, delta_ts, max_delta_ts;
  MPI_Request		mreq;
  MPI_Status		mstat;
  MPI_Comm		comm = MPI_COMM_WORLD;
  struct timeval	xx0;
#ifdef USE_RUSAGE
  struct rusage		tv0, tv1, tv00, tv0ts;
  struct rusage		mtv0, mtv1;
#else
#ifdef USE_UTIME
  clock_t		tv0, tv1, tv00, tv0ts;
  clock_t		mtv0, mtv1;
#else
  double	tv0, tv1, tv00, tv0ts;
  double	mtv0, mtv1;
#endif
#endif
  useconds_t		sleep_time = 1000;
  double		msec, stx, rtx;
  unsigned long		s2vec[GENRAND_VLEN+1];
  SHA_CTX		shainfo;
  char			shadigest1[20], shadigest2[20];
#ifdef PE_CHPKT
  callbacks_t 		cbt = { p_ck_cb, p_rs_cb, p_rm_cb };
#endif

  /*
   * parse args
   */

  gettimeofday(&xx0, 0);
  GET_CLOCK(tv00);
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(comm, &p_myrank);
#ifdef PE_CHKPT
  i = mpc_set_ckpt_callbacks(&cbt);
  if (p_myrank == 0)
    printf("mpc_set_ckpt_callbacks: return val: %d\n", i);
#endif

  {
    char		**cpp;
    for (cpp=argv+1; *cpp; ++cpp) {
      if (**cpp == '-') {
	switch ((*cpp)[1]) {
	case 't':
	  maxtime = (double)atoi(*(++cpp)) * 1000.0;
	  break;
	case 'T':
	  maxtime = (double)atoi(*(++cpp));
	  break;
	case 'v':
	  ++verbose;
	  break;
	case 'n':
	  loopmax = atoi(*(++cpp));
	  break;
	case 'E':
	  throttle = 0;
	  break;
	case 'u':
	  sleep_time = atoi(*(++cpp))*1000;
	  break;
	default:
	  fprintf(stderr,"usage: pchksum [-t secs] [-T msecs] [-v] [-n loopcount]\n");
	  exit(1);
	}
      }
      else {
	fprintf(stderr,"usage: pchksum [-t secs] [-T msecs] [-v] [-n loopcount]\n");
	exit(1);
      }
    }
    if (((loopmax<0) && (maxtime<0.0)) || ((loopmax>0) && (maxtime>0.0))) {
      fprintf(stderr, "Error: specify only time or loopcount\n");
      exit(1);
    }
  }
  /*
   * initialization
   */
  MPI_Comm_rank(comm, &myrank);
  MPI_Comm_size(comm, &nnode);
  nodecntrl = nnode/2;
  to   = malloc(sizeof(int)*nnode);
  from = malloc(sizeof(int)*nnode);
  initrandvec(myrank, s2vec);
  buflen = sizeof(uint64_t)*BUFFLEN + sizeof(unsigned long);
  rbuf0 = malloc(buflen);
  sbuf0 = malloc(buflen);
  tbuf0 = malloc(buflen);
  rcv_ts = (unsigned long*)rbuf0;
  snd_ts = (unsigned long*)sbuf0;
  t_ts   = (unsigned long*)tbuf0;
  rbuff = (uint64_t *)(rcv_ts + 1);
  sbuff = (uint64_t *)(snd_ts + 1);
  tbuff = (uint64_t *)(t_ts + 1);
  memset(rbuf0, '\0', buflen);
  csp = (unsigned char *)sbuff;
  ctp = (unsigned char *)tbuff;
  for (i=0; i<BUFFLEN*sizeof(uint64_t); ++i)
    csp[i] = ctp[i] = genrand_r(s2vec)%256;
  SHAInit(&shainfo);
  SHAUpdate(&shainfo, (char *)tbuff, sizeof(uint64_t)*BUFFLEN);
  SHAFinal(shadigest1, &shainfo);
  if ((!myrank) && (verbose)) {
    printf(" Number of tasks: %d\n", nnode);
    printf(" Initial digest\n ");
    for (i=0; i<20; ++i) 
      printf("%02x", shadigest1[i]);
    printf("\n");
#ifdef USE_RUSAGE
    {
      struct timeval xxt;
      long	xttt;
      GET_CLOCK(tv0);
      gettimeofday(&xxt,0);
      xttt = (xxt.tv_sec - xx0.tv_sec)*1000000 + (xxt.tv_usec - xx0.tv_usec);
      printf(" Using rusage for a clock: time = %d usec  (w %d)\n", DELTA_TV2USEC(tv0,tv00), xttt );
    }
#else
#ifdef USE_UTIME
    printf(" Using User time for a clock\n");
#endif
#endif
  }
  initrandvec(1, svec);
  max_delta_ts = 0;
  /*
   * XOR merge - forward loop
   */
  MPI_Barrier(comm);
  GET_CLOCK(tv0);
  tv0ts = tv0;
  if (maxtime > 0.0)
    maxtime -= 4.0*DELTA_TV2MSEC(tv0,tv00);
  for (stx=0.0, j=0; (loopmax<0) || (j<loopmax); ++j) {
    if ((myrank == nodecntrl) && (loopmax<0)) {
      GET_CLOCK(tv1);
      msec = DELTA_TV2MSEC(tv1,tv0);
      if ((msec > (maxtime/2))) {
	if (verbose>2) {
	  printf("[%3d]  Time interval reached sending abort: loopcount=%d\n", myrank, j);
	  fflush(stdout);
	}
	itmp = j + 5;
	for (jnode=0; jnode<nnode; ++jnode)
	  MPI_Send(&itmp, 1, MPI_INT, jnode, aborttag, comm);
      }
    }
    if (j < MAXREPLAY) {
      gettofrom(nnode, to, from);
      for (i=0; i<nnode; ++i) {
	assert((from[to[i]] == i));
	for (k=0; k<nnode; ++k) {
	  if (i!=k)
	    assert((to[i] != to[k]));
	}
      }
      tfr[j].to   = to[myrank];
      tfr[j].from = from[myrank];
    }
    jj = j % MAXREPLAY;
    GET_CLOCK(mtv0);
    *snd_ts = DELTA_TV2USEC(mtv0, tv0ts);
    MPI_Irecv(rbuf0, buflen, MPI_BYTE, tfr[jj].from, ttag, comm, &mreq);
    MPI_Send(sbuf0,  buflen, MPI_BYTE, tfr[jj].to,   ttag, comm);
    MPI_Wait(&mreq, &mstat);
    delta_ts = labs(*rcv_ts - *snd_ts);
    max_delta_ts = MAX(max_delta_ts, delta_ts);
    stx += buflen;
    if (loopmax<0) {
      abortflg = 0;
      MPI_Iprobe(MPI_ANY_SOURCE, aborttag, comm, &abortflg, &mstat);
      if (abortflg != 0) {
	MPI_Recv(&itmp, 1, MPI_INT, nodecntrl, aborttag, comm, &mstat);
	assert((j<itmp));
	if (verbose>2) {
	  printf("[%3d]  Abort signal recieved: loopcount=%d  loopmax=%d\n", myrank, j, itmp);
	  fflush(stdout);
	}
	loopmax = itmp;
      }
    }
    XOR_merge(BUFFLEN, tbuff, rbuff);
    /*
    if ((throttle) && (*rcv_ts > *snd_ts)) {
      sleep_time = delta_ts/sleep_factor;
      usleep(sleep_time);
    }
    */
    usleep(sleep_time);
  }
  if ((!myrank)) {
    if (verbose) {
      printf(" Forward merge complete  ( tsub = %d sec)\n", (int)(tsub/1000000));
      GET_CLOCK(tv1);
      msec = DELTA_TV2MSEC(tv1,tv0);
      printf(" Elapsed time: %.2f msecs\n", msec);
      printf(" Outbound data volume: %.2f MB\n", stx/(1024.0*1024.0));
    }
    if ((verbose) || (maxtime>0.0))
      printf(" Iteration count: %d\n", loopmax);
  }
  MPI_Barrier(comm);
  /*
   * XOR merge - in reverse order
   */
  GET_CLOCK(tv0);
  for (j=loopmax-1; j>=0; --j) {
    jj = j % MAXREPLAY;
    GET_CLOCK(mtv0);
    *snd_ts = DELTA_TV2USEC(mtv0, tv0ts);
    MPI_Irecv(rbuf0, buflen, MPI_BYTE, tfr[jj].from, ttag, comm, &mreq);
    MPI_Send(sbuf0,  buflen, MPI_BYTE, tfr[jj].to,   ttag, comm);
    MPI_Wait(&mreq, &mstat);
    delta_ts = labs(*rcv_ts - *snd_ts);
    max_delta_ts = MAX(max_delta_ts, delta_ts);
    XOR_merge(BUFFLEN, tbuff, rbuff);
    /*
    if ((throttle) && (*rcv_ts > *snd_ts)) {
      sleep_time = delta_ts/sleep_factor;
      usleep(sleep_time);
    }
    */
    usleep(sleep_time);
  }
  MPI_Barrier(comm);
  SHAInit(&shainfo);
  SHAUpdate(&shainfo, (char *)tbuff, sizeof(uint64_t)*BUFFLEN);
  SHAFinal(shadigest2, &shainfo);
  /*
   * optional printout
   */
  if ((!myrank) && (verbose)) {
    printf(" Reverse merge complete\n");
    GET_CLOCK(tv1);
    msec = DELTA_TV2MSEC(tv1,tv0);
    printf(" Elapsed time: %.2f msecs\n", msec);
    printf(" Final digest\n ");
    for (i=0; i<20; ++i) 
      printf("%02x", shadigest2[i]);
    printf("\n");
    printf(" Max stagger delta: %d usecs\n", max_delta_ts);
  }
  /*
   * check status and finish
   */
  free(to); free(from);
  for (j=0, i=0; i<20; ++i)
    j |= (shadigest1[i] != shadigest2[i]);
  MPI_Allreduce(&j, &itmp, 1, MPI_INT, MPI_BOR, comm);
  MPI_Finalize();
  if ((!myrank)) {
    if ((verbose) || (maxtime>0.0)) {
      GET_CLOCK(tv1);
      msec = DELTA_TV2MSEC(tv1,tv00)/1000.0;
      printf(" Total elapsed time: %.2f secs\n", msec);
    }
    if (verbose)
      printf(" Status: %s\n", ((itmp)?"Failed":"OK"));
  }
  return (itmp);
}




void XOR_merge( int n, uint64_t p[], const uint64_t q[] )
{
  int			i;
  for (i=0; i<n; ++i) 
    p[i] ^= q[i];
}



void gettofrom( int p, int to[], int from[] )
{
  int			i, ii, j, k;


 reset:  
  for (i=0; i<p; ++i)
    to[i] = from[i] = -1;
  for (i=0; i<p; ++i) {
    ii = 1 - 2*(i%2);
    j = genrand_r(svec)%p;
    for (k=0; ((i==j) || (from[j]>=0)) && (k<p); ++k)
      j = ((j+=ii)<0) ? (p-1) : (j>(p-1)) ? 0 : j;
    if (k == p) {
      goto reset;
    }
    to[i] = j;
    from[j] = i;
  }
}

