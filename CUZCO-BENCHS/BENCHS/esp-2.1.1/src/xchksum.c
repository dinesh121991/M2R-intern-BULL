#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "genrand.h"
#include "sha1.h"


/*
 *   xchksum
 *
 *   Usage: xchksum
 *
 *   
 */


#define BUFFLEN			46543          		/* 64-bit words */


int main(int argc, char *(argv[]) )
{
  int			i,it,buflen;
  uint64_t		*tbuff;
  unsigned long		svec[GENRAND_VLEN+1];
  SHA_CTX		shainfo;
  char			shadigest1[20], shadigest2[20];
  unsigned char         *ctp;

  buflen = sizeof(uint64_t)*BUFFLEN + sizeof(unsigned long);
  tbuff = (uint64_t *)(malloc(buflen) + 1);
  ctp = (unsigned char *)tbuff;

  sprintf((char *)tbuff,
   "The quick brown fox jumped over the two lazy dogs.");
  SHAInit(&shainfo);
/*
  printf("debug shainfo: %d %d %d %d %d - %d %d - %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d -%d\n",
    shainfo.digest[0], 
    shainfo.digest[1], 
    shainfo.digest[2], 
    shainfo.digest[3], 
    shainfo.digest[4], 
    shainfo.countLo, 
    shainfo.countHi, 
    shainfo.data[0], 
    shainfo.data[1], 
    shainfo.data[2], 
    shainfo.data[3], 
    shainfo.data[4], 
    shainfo.data[5], 
    shainfo.data[6], 
    shainfo.data[7], 
    shainfo.data[8], 
    shainfo.data[9], 
    shainfo.data[10], 
    shainfo.data[11], 
    shainfo.data[12], 
    shainfo.data[13], 
    shainfo.data[14], 
    shainfo.data[15], 
    shainfo.Endianness);
*/
  SHAUpdate(&shainfo, (char *)tbuff, sizeof(uint64_t)*BUFFLEN);
  SHAFinal(shadigest1, &shainfo);
  printf("Test message \"%s\"\n", tbuff);
  printf("Test digest ");
  for (i=0; i<20; ++i) printf("%02x", (unsigned char)shadigest1[i]);
  printf("\n");

  for(it=0;it<10;it++) {
   initrandvec(it, svec);
   for (i=0; i<BUFFLEN*sizeof(uint64_t); ++i)
    ctp[i] = genrand_r(svec)%256;

   SHAInit(&shainfo);
   SHAUpdate(&shainfo, (char *)tbuff, sizeof(uint64_t)*BUFFLEN);
   SHAFinal(shadigest2, &shainfo);
   printf("Random digest %d ",it);
   for (i=0; i<20; ++i) printf("%02x", (unsigned char)shadigest2[i]);
   printf("\n");
  }

}


