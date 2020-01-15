#include "ft_select.h"

static void		set_color(t_select *select, char *str)
{
	struct stat	stat;

	if (lstat(str, &stat) != -1)
	{
		if (S_ISDIR(stat.st_mode))
			ft_dprintf(2, "%{CYAN}");
		else if (S_ISLNK(stat.st_mode))
			ft_dprintf(2, "%{RED}");
		else if (S_ISBLK(stat.st_mode))
			ft_dprintf(2, "%{GREEN}");
		else if (S_ISCHR(stat.st_mode))
			ft_dprintf(2, "%{BLUE}");
		else if (S_ISFIFO(stat.st_mode) ||
				S_ISSOCK(stat.st_mode))
			ft_dprintf(2, "%{PURPLE}");
		else
			bold_cap(select);
	}
}

static void		print_search_part(t_select *select, t_dlist *node,
									t_arg* arg)
{
	ft_dprintf(2, "%{YELLOW}");
	if (node == select->current)
		position_cap(select);
	if (arg->nat_select || arg->dyn_select)
		select_cap();
	write(2, arg->str, select->len_search);
	reset_cap(select);
}

static void		print_rest(t_select *select, t_dlist *node,
							t_arg *arg, int width)
{
	set_color(select, arg->str);
	if (node == select->current)
		position_cap(select);
	if (arg->nat_select)
		select_cap();
	width -= select->len_search;
	ft_dprintf(2, "%-*s", width, &arg->str[select->len_search]);
	reset_cap(select);
}

static void		print_arg(t_select *select, t_dlist *node,
							t_arg *arg, int width)
{
	set_color(select, arg->str);
	if (node == select->current)
		position_cap(select);
	if (arg->nat_select)
		select_cap();
	ft_dprintf(2, "%-*s", width, arg->str);
	reset_cap(select);
}

void			write_arg(t_select *select, t_dlist *node, int n)
{
	t_point		pos;
	t_arg		*arg;
	int			width;

	arg = (t_arg*)node->content;
	pos = cursor_pos(*select, n);
	move_cursor(select, pos);
	width = select->lens_cols[n / select->winsize.ws_row];
	if (arg->search && select->len_search > 0)
	{
		print_search_part(select, node, arg);
		print_rest(select, node, arg, width);
	}
	else
		print_arg(select, node, arg, width);
}
