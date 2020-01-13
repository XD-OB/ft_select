#include "ft_select.h"

static void			show_cursor(t_select *select)
{
	char			*show_cap;

	if (!(show_cap = tgetstr("ve", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(show_cap, 1, ft_putint);
}

static void			hide_cursor(t_select *select)
{
	char			*hide_cap;

	if (!(hide_cap = tgetstr("vi", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(hide_cap, 1, ft_putint);
}

void				unset_ncanonic(t_select *select)
{
	char			*unsetfs_cap;

	tcsetattr(STDIN_FILENO, TCSADRAIN, &(select->old_termios));
	show_cursor(select);
	if (!(unsetfs_cap = tgetstr("te", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(tgoto(unsetfs_cap, 0, 0), 1, ft_putint);
}

void				set_ncanonic(t_select *select)
{
	struct termios	new_termios;
	char			*setfs_cap;

	if (tcgetattr(STDIN_FILENO, &new_termios))
		exit_error_fs(select, ERROR_GETATTR);
	new_termios.c_lflag &= ~(ICANON);
	new_termios.c_lflag &= ~(ECHO);
	new_termios.c_cc[VMIN] = 1;
	new_termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &new_termios))
		exit_error_fs(select, ERROR_SETATTR);
	hide_cursor(select);
	if (!(setfs_cap = tgetstr("ti", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(tgoto(setfs_cap, 0, 0), 1, ft_putint);
}
