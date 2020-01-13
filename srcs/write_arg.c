#include "ft_select.h"

t_point			cursor_pos(t_select select, int n)
{
	t_point		pos;
	int			tmp;
	int			i;

	pos.x = 0;
	pos.y = n % select.rows;
	tmp = n / select.rows;
	i = -1;
	while (++i < tmp)
		pos.x += select.lens_cols[i] + 2;
	return (pos);
}

static void		reset_cap(t_select *select)
{
	char		*reset_cap;

	if (!(reset_cap = tgetstr("me", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(reset_cap, 1, ft_putint);
}

static void		position_cap(t_select *select)
{
	char		*underline_cap;

	if (!(underline_cap = tgetstr("us", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(underline_cap, 1, ft_putint);
}

static void		select_cap(t_select *select)
{
	tputs("\e[7m", 1, ft_putint);
}

void			write_arg(t_select *select, t_dlist *node, int n)
{
	char		*cm_cap;
	t_arg		*arg;
	t_point		pos;
	int			width;

	arg = (t_arg*)node->content;
	pos = cursor_pos(*select, n);
	move_cursor(select, pos);
	if (node == select->current)
		position_cap(select);
	if (arg->select)
		select_cap(select);
	width = select->lens_cols[n / select->rows];
	ft_putstr_fd(arg->str, 2);
	reset_cap(select);
}
