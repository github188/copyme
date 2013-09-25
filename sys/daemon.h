
#ifndef DAEMON_H
#define DAEMON_H

/* 将一个进程变成守护进程 */
int daemon_init(const char *pname, int facility);

#endif
