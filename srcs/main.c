#include "ft_select.h"

static int			is_arrow(int key)
{
	if (key == KEY_RIGHT)
		return (1);
	else if (key == KEY_LEFT)
		return (1);
	else if (key == KEY_DOWN)
		return (1);
	else if (key == KEY_UP)
		return (1);
	return (0);
}

void				launch_select(t_select *select)
{
	int				buff;

	buff = 0;
	set_ncanonic(select);
	draw_state(select);
	while (read(STDIN_FILENO, &buff, 4) != 0)
	{
		if (buff == KEY_ESC)
			break ;
		else if (is_arrow(buff))
			move_arrow(select, buff);
		else if (buff == KEY_SPACE)
			select_elem(select);
		else if (buff == KEY_DEL || buff == KEY_BSPACE)
			delete_elem(select);
		else if (buff == KEY_ENTER)
			print_selected(select);
		buff = 0;
	}
}
/*
t_select		*get_select(void)
{
	static t_select		select;

	return (&select);
}

void			kill_handler(int sig)
{
	t_select	*select;

	select = get_select();
	if (sig == SIGINT)
	{
		exit_error_fs(select, ERROR_ALLOC);
	}
}

void			signal_handlers()
{
	signal(SIGINT, &kill_handler);
	
	signal(SIGHUP, &exit_handler);
	signal(SIGKILL, &exit_handler);
	signal(SIGTERM, &exit_handler);
	signal(SIGSTOP, &exit_handler);
	signal(SIGTSTP, &exit_handler);
	signal(SIGQUIT, &exit_handler);
	signal(SIGILL, &exit_handler);
	signal(SIGABRT, &exit_handler);
	signal(SIGTRAP, &exit_handler);
	signal(SIGEMT, &exit_handler);
	signal(SIGFPE, &exit_handler);
	signal(SIGBUS, &exit_handler);
	signal(SIGSEGV, &exit_handler);
	signal(SIGSYS, &exit_handler);
	signal(SIGTTIN, &exit_handler);
	signal(SIGTTOU, &exit_handler);
	signal(SIGXCPU, &exit_handler);
	signal(SIGXFSZ, &exit_handler);
	signal(SIGVTALRM, &exit_handler);
	signal(SIGALRM, &exit_handler);
	signal(SIGPROF, &exit_handler);
	signal(SIGTSTP, &exit_handler);
	signal(SIGCONT, &exit_handler);
	signal(SIGWINCH, &draw_args);
}
*/
int		main(int ac, char **av)
{
	t_select	select;

	init_term();
	signal_handlers();
	init_select(&select, ac, av);
	launch_select(&select);
	//print_select(select);			//////////
	free_select(&select);
	return (EXIT_SUCCESS);
}
