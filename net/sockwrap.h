
#ifndef SOCK_WRAP_H
#define SOCK_WRAP_H

#include"netcommon.h"

int Socket(int family, int type, int protocol);

void Bind(int sockfd, struct sockaddr *pAddr, socklen_t len);

void Listen(int sockfd, int listenq);

int Accept(int sockfd, struct sockaddr *pAddr, socklen_t* len);

#endif
