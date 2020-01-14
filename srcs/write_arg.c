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

void			bold_cap(t_select *select)
{
	char		*bold_cap;

	if (!(bold_cap = tgetstr("md", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(bold_cap, 1, ft_putint);
}

void			set_color(char *str)
{
	struct stat		stat;

	if (lstat(str, &stat) != -1)
	{
		if (S_ISDIR(stat.st_mode))
			ft_dprintf(2, "%{cyan}");
		else if (S_ISLNK(stat.st_mode))
			ft_dprintf(2, "%{red}");
		else if (S_ISBLK(stat.st_mode))
			ft_dprintf(2, "%{green}");
		else if (S_ISCHR(stat.st_mode))
			ft_dprintf(2, "%{blue}");
		else if (S_ISFIFO(stat.st_mode) ||
				S_ISSOCK(stat.st_mode))
			ft_dprintf(2, "%{purple}");
	}
}

void			temp_select_cap(t_select *select)
{
	(void)select;
	ft_dprintf(2, "%{yellow}");
	select_cap(select);
}

/*static */void		print_search_part(t_select *select, t_dlist *node)
{
	t_arg		*arg;

	arg = (t_arg*)node->content;
	set_color(arg->str);
	if (node == select->current)
		position_cap(select);
	if (arg->dyn_select)
		temp_select_cap(select);
	if (arg->nat_select)
		select_cap(select);
	if (arg->search)
		bold_cap(select);
	write(2, arg->str, select->len_search);
	reset_cap(select);
}

void		print_rest(t_select *select, t_dlist *node, int width)
{
	t_arg		*arg;

	arg = (t_arg*)node->content;
	set_color(arg->str);
	if (node == select->current)
		position_cap(select);
	if (arg->dyn_select)
		temp_select_cap(select);
	if (arg->nat_select)
		select_cap(select);
	width -= select->len_search;
	ft_dprintf(2, "%-*s", width, &arg->str[select->len_search]);
	reset_cap(select);
}

void			write_arg(t_select *select, t_dlist *node, int n)
{
	t_point		pos;
	int			width;

	pos = cursor_pos(*select, n);
	move_cursor(select, pos);
	width = select->lens_cols[n / select->winsize.ws_row];
	if (select->len_search > 0)
		print_search_part(select, node);
	print_rest(select, node, width);
}
