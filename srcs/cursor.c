#include "ft_select.h"

t_point			cursor_pos(t_select select, int n)
{
	t_point		pos;
	int			tmp;
	int			i;

	pos.x = 0;
	pos.y = n % select.winsize.ws_row;
	tmp = n / select.winsize.ws_row;
	i = -1;
	while (++i < tmp)
		pos.x += select.lens_cols[i] + 2;
	return (pos);
}

void			move_cursor(t_select *select, t_point p)
{
	char		*cm_cap;

	if (!(cm_cap = tgetstr("cm", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(tgoto(cm_cap, p.x, p.y), 1, ft_putint);
}
