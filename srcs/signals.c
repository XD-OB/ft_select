#include "ft_select.h"

static void		sig_handler(int sig)
{
	t_select	**aselect;

	aselect = get_aselect();
	if (sig == SIGTSTP)
	{
		unset_ncanonic(*aselect);
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDIN_FILENO, TIOCSTI, "\x1A");
	}
	else if (sig == SIGCONT)
	{
		set_ncanonic(*aselect);
		draw_state(*aselect);
	}
	//else if (sig == SIGWINCH)
	//{
	//}
	else
	{
		free_select(*aselect);
		exit(1);
	}
}

static void		win_handler(int sig)
{
	t_select	**aselect;

	(void)sig;
	aselect = get_aselect();
	ioctl(STDIN_FILENO, TIOCGWINSZ,
			&((*aselect)->winsize));
	draw_state(*aselect);
}

void			signal_handlers(void)
{
	signal(SIGVTALRM, &sig_handler);
	signal(SIGTSTP, &sig_handler);
	signal(SIGCONT, &sig_handler);
	signal(SIGKILL, &sig_handler);
	signal(SIGTERM, &sig_handler);
	signal(SIGSTOP, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	signal(SIGABRT, &sig_handler);
	signal(SIGPROF, &sig_handler);
	signal(SIGXCPU, &sig_handler);
	signal(SIGXFSZ, &sig_handler);
	signal(SIGTTIN, &sig_handler);
	signal(SIGTTOU, &sig_handler);
	signal(SIGALRM, &sig_handler);
	signal(SIGPIPE, &sig_handler);
	signal(SIGSEGV, &sig_handler);
	signal(SIGTRAP, &sig_handler);
	signal(SIGINT, &sig_handler);
	signal(SIGHUP, &sig_handler);
	signal(SIGILL, &sig_handler);
	signal(SIGSYS, &sig_handler);
	signal(SIGURG, &sig_handler);
	signal(SIGFPE, &sig_handler);
	signal(SIGBUS, &sig_handler);
	signal(SIGWINCH, &win_handler);
}
