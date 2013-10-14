
#ifndef DAEMON_H
#define DAEMON_H

/* 在进程中调用该函数，将使其变成守护进程 */
int daemon_init(const char *pname, int facility);

#endif
