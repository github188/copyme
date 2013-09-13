
#ifndef PN_SOCK_TOOL
#define PN_SOCK_TOOL
#include<sys/types.h>

/* Get host's byte order
RETURN: 0 for failed, 1 for little-endian -1 for big-endian */
int PNByteorder(void);

/* Read n bytes form descriptor fd 
RETURN: -1 for error, >=0 on success
 */
ssize_t PNReadn(int fd, void* vptr, size_t n);

/* Same as system call read
 */
ssize_t PNRead(int fd, void* vprt, size_t n);

/* Write n bytes to descriptr fd from vptr 
RETURN: -1 for error, n on success */
ssize_t PNWriten(int fd, const void *vprt, size_t n);

typedef void Sigfunc(int);

Sigfunc *PNSignal(int signo, Sigfunc *func);


#endif // PN_SOCK_TOOL
