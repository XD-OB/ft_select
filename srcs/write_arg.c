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
	(void)select;
	tputs("\e[7m", 1, ft_putint);
}

static void		blink_cap(t_select *select)
{
	char		*blink_cap;

	if (!(blink_cap = tgetstr("md", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(blink_cap, 1, ft_putint);
}

void			print_arg(char *str, int width)
{
	struct stat		stat;

	if (lstat(str, &stat) != -1)
	{
		if (S_ISDIR(stat.st_mode))
			ft_dprintf(2, "%{CYAN}%-*s", width, str);
		else if (S_ISLNK(stat.st_mode))
			ft_dprintf(2, "%{RED}%-*s", width, str);
		else if (S_ISSOCK(stat.st_mode))
			ft_dprintf(2, "%{YELLOW}%-*s", width, str);
		else if (S_ISBLK(stat.st_mode))
			ft_dprintf(2, "%{GREEN}%-*s", width, str);
		else if (S_ISCHR(stat.st_mode))
			ft_dprintf(2, "%{BLUE}%-*s", width, str);
		else if (S_ISFIFO(stat.st_mode))
			ft_dprintf(2, "%{PURPLE}%-*s", width, str);
		else
			ft_dprintf(2, "%-*s", width, str);
	}
	else
		ft_dprintf(2, "%-*s", width, str);
}

void			write_arg(t_select *select, t_dlist *node, int n)
{
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
	if (select->sight && arg->blink)
		blink_cap(select);
	width = select->lens_cols[n / select->winsize.ws_row];
	print_arg(arg->str, width);
	reset_cap(select);
}
