/* sha1types.h */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_ 1

#include <sys/types.h>
#include <stdint.h>

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT4 defines a four byte word */
typedef uint32_t UINT4; 

/* BYTE defines a unsigned character */
typedef unsigned char BYTE;

#ifndef TRUE
  #define FALSE	0
  #define TRUE	( !FALSE )
#endif /* TRUE */

#endif /* end _GLOBAL_H_ */
