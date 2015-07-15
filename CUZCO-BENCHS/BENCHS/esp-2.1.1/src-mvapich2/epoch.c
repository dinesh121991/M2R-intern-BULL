#include <sys/types.h>
#include <stdio.h>
/*
 * print current time in seconds from Epoch
 */

int main( int argc, char *(argv[]) )
{
  time_t		e;

  e = time(0);
  printf("%d\n", e);
  return 0;
}

