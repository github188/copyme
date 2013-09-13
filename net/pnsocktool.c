
#include"pnsocktool.h"

#include<errno.h>
#include<signal.h>

int PNByteorder()
{
	union {
		short s;
		char c[sizeof(short)];
	} un;

	un.s = 0x0102;
	if( sizeof(short) == 2 ) {
		if( un.c[0] == 1 && un.c[1] == 2)
		  return -1;
		else if( un.c[0] == 2 && un.c[1] == 1 )
		  return 1;
		else 
		  return 0;
	} else {
		return 0;
	}
}

ssize_t PNReadn(int fd, void* vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while( nleft > 0 ) {
		if( (nread = read(fd, ptr, nleft)) < 0 ) {
			if(errno == EINTR)
			  nread = 0;
			else
			  return (-1); /* ERROR */
		} else if(nread == 0)
		  break; /* EOF */

		nleft -= nread;
		ptr += nread;
	}

	return ( n - nleft);

}

ssize_t PNRead(int fd, void* vptr, size_t n)
{
	ssize_t ret;
	while(1) {
		if( (ret = read(fd, vptr, n)) < 0 ) {
			if(errno == EINTR) {
				// printf("PNRead, EINTR returned. \n");
				continue;
			} else {
				break;
			}
		} else {
			// printf("PNRead, ret = %d\n",ret);
			break;
		}
	}
	return ret;
}


ssize_t PNWriten(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while(nleft > 0) {
		if( (nwritten = write(fd, ptr, nleft) ) <= 0 ) {
			if(nwritten < 0 && errno == EINTR)
			  nwritten = 0;
			else
			  return(-1);
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return(n);
}

Sigfunc* PNSignal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(signo == SIGALRM) {
#ifdef SA_INTERRUPT
		// act.sa_flags |= SA_INTERRUPT; /* SunOS */
#endif
	} else {
#ifdef SA_RESTART
		// printf("SA_RESTART....\n");
		// act.sa_flags |= SA_RESTART; /* SVR4, 4.4BSD */
#endif
	}
	if( sigaction(signo, &act, &oact) < 0 )
	  return (SIG_ERR);
	return(oact.sa_handler);
}

