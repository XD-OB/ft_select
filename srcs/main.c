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
	curr = select-> args;
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

static void			press_tab(t_select *select)
{
	if (select->take)
	{
		select->take =  0;
		to_natural(select);
	}
	else
		select->take = 1;
	select->len_search = 0;
	draw_state(select);
}

void				launch_select(t_select *select)
{
	int				buff;

	buff = 0;
	set_ncanonic(select);
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
		else if (ft_isprint(buff))
		{
			if (select->take)
				search_take(select, buff);
		}
		buff = 0;
	}
}

int		main(int ac, char **av)
{
	t_select	**aselect;
	t_select	select;

	aselect = get_aselect();
	*aselect = &select;
	init_term();
	signal_handlers();
	init_select(&select, ac, av);
	launch_select(&select);
	//print_select(select);			//////////
	free_select(&select);
	return (EXIT_SUCCESS);
}
