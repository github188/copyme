

extern int daemon_proc;

#define MAXFD 64

int daemon_init(const char *pname, int facility)
{
	int i;
	pid_t pid;
	if( (pid = fork()) < 0)
		return (-1);
	else if(pid)
		_exit(0);
	/* 此时脱离了创建父进程的shell，
	 * 且当前进程不是一个进程组的头进程
	 * 可以调用setsid了 */

	if(setsid() < 0) /* Create a new session */
		return (-1);
	signal(SIGHUP, SIG_IGN);
	if( (pid = fork()) < 0)
		return (-1);
	else if(pid)
		_exit(0); // 上面忽略SIGHUP是因为这里会产生SIGHUP
	/* 再次fork是为了确保本守护进程将来即使打开一个终端设备
	 * 也不会自动获得控制终端,(新的子进程不是会话头进程),参见APUE */

	daemon_proc = 1; // 方便调用该函数的进程设置此变量来判断运行方式
	chdir("/"); // 改变工作目录,
	for(i = 0; i < MAXFD; i++)
		close(i);

	/* 重定向 stdin stdout stderr */
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);

	return (0);
}
