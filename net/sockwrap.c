#include"sockwrap.h"
#include"error.h"

int Socket(int family, int type, int protocol)
{
	int n;
	if( (n = socket(family, type, protocol) ) < 0 )
	  err_sys("socket error");
	return (n);
}

void Bind(int sockfd, struct sockaddr *pAddr, socklen_t len)
{
	if( bind(sockfd, pAddr, len) < 0 )
	  err_sys("bind error");
}

void Listen(int sockfd, int listenq)
{
	char *ptr;
	if( (ptr = getenv("LISTENQ")) != NULL)
	  listenq = atoi(ptr);

	if(listen(sockfd, listenq) < 0 )
	  err_sys("listen error");
}

int Accept(int sockfd, struct sockaddr *pAddr, socklen_t* len)
{
	int n;
	if( (n = accept(sockfd, pAddr, len) ) < 0 )
	  err_sys("accept error");
	return (n);
}

