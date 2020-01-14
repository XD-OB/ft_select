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

static void			to_natural(t_select *select)
{
	t_dlist			*curr;
	t_arg			*arg;
	size_t			i;

	i = 0;
	curr = select->args;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (arg->dyn_select)
		{
			arg->nat_select = 1;
			arg->dyn_select = 0;
			arg->search = 0;
		}
		curr = curr->next;
	}
}

static void			sound_terminal(void)
{
	char			*sound_cap;

	sound_cap = tgetstr("bl", NULL);
	tputs(sound_cap, 1, ft_putint);
}

static void			press_tab(t_select *select)
{
	sound_terminal();
	if (select->take)
	{
		select->take = 0;
		to_natural(select);
	}
	else
		select->take = 1;
	select->len_search = 0;
	draw_state(select);
}

char				*

void				enter_rep(t_select *select)
{
	struct dirent	*dirent;
	t_dlist			*node;
	t_arg			*arg;
	char			*path;
	char			*parent;
	DIR				*dir;

	arg = (t_arg*)select->current->content;
	dir = opendir(arg->str);
	if (!dir)
		return ;
	parent = ft_strdup(arg->str);
	if (select->lens_cols)
		free(select->lens_cols);
	if (select->args)
		dct_lstdel(&(select->args), delete_arg);
	select->args = NULL;
	select->lens_cols = NULL;
	select->nbr_cols = 0;
	select->len_search = 0;
	select->nbr_args = 0;
	dirent = readdir(dir);
	while (dirent)
	{
		path = full_path(parent, dirent->d_name)
		arg = create_arg(path);
		free(path);
		node = dct_lstnew_sm(arg, sizeof(arg));
		dct_lstadd_last(&(select->args), node);
		select->nbr_args++;
		dirent = readdir(dir);
	}
	free(parent);
	select->current = select->args;
	draw_state(select);
}

void				launch_select(t_select *select)
{
	int				buff;

	buff = 0;
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
		else if (buff == KEY_TAB)
			press_tab(select);
		else if (buff == KEY_FSPACE)
			enter_rep(select);
		else if (ft_isprint(buff))
			search_engine(select, buff);
		buff = 0;
	}
}
