#include "ft_select.h"

static void		set_color(char *str)
{
	struct stat	stat;

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

static void		print_search_part(t_select *select, t_dlist *node)
{
	t_arg		*arg;

	arg = (t_arg*)node->content;
	set_color(arg->str);
	if (node == select->current)
		position_cap(select);
	if (arg->dyn_select)
		tmp_select_cap();
	if (arg->nat_select)
		select_cap();
	if (arg->search)
		search_cap(select);
	write(2, arg->str, select->len_search);
	reset_cap(select);
}

static void		print_rest(t_select *select, t_dlist *node, int width)
{
	t_arg		*arg;

	arg = (t_arg*)node->content;
	set_color(arg->str);
	if (node == select->current)
		position_cap(select);
	if (arg->dyn_select)
		tmp_select_cap();
	if (arg->nat_select)
		select_cap();
	width -= select->len_search;
	ft_dprintf(2, "%-*s", width, &arg->str[select->len_search]);
	reset_cap(select);
}

static void		write_arg(t_select *select, t_dlist *node, int n)
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

void			write_args(t_select *select)
{
	t_dlist		*curr;
	int			n;

	n = 0;
	curr = select->args;
	write_arg(select, curr, n++);
	curr = curr->next;
	while (curr != select->args)
	{
		write_arg(select, curr, n);
		curr = curr->next;
		n++;
	}
}
