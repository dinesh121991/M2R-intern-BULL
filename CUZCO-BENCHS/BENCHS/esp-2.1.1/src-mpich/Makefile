
#               MPICC = mpcc_r
               MPICC = mpicc.mpich
 #                 CC = pathcc
  #                CC = xlc_r
                  CC = gcc

             DEFINES = 
#-DDEBUG=

              CFLAGS = -O $(DEFINES)

             LDFLAGS = $(CFLAGS) 
                  RM = /bin/rm

all: test_chksum xchksum pchksum epoch

pchksum.o: pchksum.c
	$(MPICC) $(CFLAGS) -c pchksum.c

xchksum: genrand.o sha1.o xchksum.o
	$(CC) -o xchksum genrand.o sha1.o xchksum.o $(LIBS)

test_chksum: xchksum
	./xchksum | grep "Test digest"
	@grep "Test digest" xchksum_reference_output.txt
	@echo "The above digests should match"

pchksum: genrand.o sha1.o pchksum.o
	$(MPICC) -o pchksum genrand.o sha1.o pchksum.o $(LIBS)


expoch: epoch.c
	$(CC) -o epoch epoch.c

clean:
	$(RM) -f *.o xchksum pchksum epoch


