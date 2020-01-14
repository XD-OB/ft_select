#include "ft_select.h"

t_arg				*create_arg(char *str)
{
	t_arg			*arg;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))))
		exit_error(ERROR_ALLOC);
	arg->str = ft_strdup(str);
	arg->dyn_select = 0;
	arg->nat_select = 0;
	arg->search = 0;
	return (arg);
}

void				move_cursor(t_select *select, t_point p)
{
	char			*cm_cap;

	if (!(cm_cap = tgetstr("cm", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(tgoto(cm_cap, p.x, p.y), 1, ft_putint);
}

void				clear_terminal(void)
{
	char			*clear_cap;

	clear_cap = tgetstr("cl", NULL);
	tputs(clear_cap, 1, ft_putint);
}

t_select			**get_aselect(void)
{
	static t_select	*select = NULL;

	return (&select);
}

int					ft_putint(int c)
{
	write(2, &c, 1);
	return (0);
}
