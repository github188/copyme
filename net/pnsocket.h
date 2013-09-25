#ifndef PN_SOCKET_H
#define PN_SOCKET_H

#include "netcommon.h"

/* 根据主机名和服务名称创建一个TCP连接 */
int tcp_connect(const char *host, const char *serv);

#endif // PN_SOCKET_H
