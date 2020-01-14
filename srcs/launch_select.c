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


static char			*full_path(char *parent, char *name)
{
	char			*res;
	char			*tmp;

	if (parent[ft_strlen(parent) - 2] == '/')
		res = ft_strjoin(parent, name);
	else
	{
		tmp = ft_strjoin(parent, "/");
		res = ft_strjoin(tmp, name);
		free(tmp);
	}
	return (res);
}

static void			empty_select(t_select *select)
{
	if (select->lens_cols)
		free(select->lens_cols);
	if (select->args)
		dct_lstdel(&(select->args), delete_arg);
	select->args = NULL;
	select->lens_cols = NULL;
	select->nbr_cols = 0;
	select->len_search = 0;
	select->nbr_args = 0;
}

static void			add_element(struct dirent *dirent,
					t_select *select, char *parent)
{
	t_dlist			*node;
	char			*path;
	t_arg			*arg;

	if (ft_strcmp(dirent->d_name, "..") &&
		ft_strcmp(dirent->d_name, "."))
	{
		path = full_path(parent, dirent->d_name);
		arg = create_arg(path);
		free(path);
		node = dct_lstnew_sm(arg, sizeof(arg));
		dct_lstadd_last(&(select->args), node);
		select->nbr_args++;
	}
}

void				enter_rep(t_select *select)
{
	struct dirent	*dirent;
	char			*parent;
	DIR				*dir;

	arg = (t_arg*)select->current->content;
	dir = opendir(arg->str);
	if (!dir)
		return ;
	parent = ft_strdup(arg->str);
	empty_select(select);
	dirent = readdir(dir);
	while (dirent)
	{
		add_element(dirent, select, parent);
		dirent = readdir(dir);
	}
	free(parent);
	closedir(dir);
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
