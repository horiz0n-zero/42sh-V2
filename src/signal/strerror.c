
#include "shell.h"

static const char *const 	g_errors[] =
{
	[SIGHUP] = "terminal line hangup",
	[SIGINT] = "interrupt program",
	[SIGQUIT] = "quit program",
	[SIGILL] = "illegal instruction",
	[SIGTRAP] = "trace trap",
	[SIGABRT] = "abort program",
	[SIGEMT] = "emulate instruction executed",
	[SIGFPE] = "floating-point exception",
	[SIGKILL] = "kill program",
	[SIGBUS] = "bus error",
	[SIGSEGV] = "segmentation violation",
	[SIGSYS] = "non-existent system call invoked",
	[SIGPIPE] = "write on a pipe with no reader",
	[SIGALRM] = "real-time timer expired",
	[SIGTERM] = "software termination signal",
	[SIGURG] = "urgent condition present on socket",
	[SIGSTOP] = "stop (cannot be caught or ignored)",
	[SIGTSTP] = "stop signal generated from keyboard",
	[SIGCONT] = "continue after stop",
	[SIGCHLD] = "child status has changed",
	[SIGTTIN] = "background read attempted from control terminal",
	[SIGTTOU] = "background write attempted to control terminal",
	[SIGIO] = "I/O is possible on a descriptor (see fcntl(2))",
	[SIGXCPU] = "cpu time limit exceeded (see setrlimit(2))",
	[SIGXFSZ] = "file size limit exceeded (see setrlimit(2))",
	[SIGVTALRM] = "virtual time alarm (see setitimer(2))",
	[SIGPROF] = "profiling timer alarm (see setitimer(2))",
	[SIGWINCH] = "Window size change",
	[SIGINFO] = "status request from keyboard",
	[SIGUSR1] = "User defined signal 1",
	[SIGUSR2] = "User defined signal 2"
};

const char				*str_error(const int signal)
{
	return (g_errors[signal]);
}
