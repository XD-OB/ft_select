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

void				search_sight(t_select *select, char c)
{
	t_dlist			*curr;
	t_arg			*arg;
	char			*ref;

	ref = NULL;
	if (select->sight > 1)
	{
		curr = select->args;
		while (curr->next != select->args)
		{
			arg = (t_arg*)curr->content;
			if (arg->blank)
			{
				ref = ft_strndup(arg->str, select->sight - 1);
				break ;
			}
			curr = curr->next;
		}
		if (!ref)
		{
			arg = (t_arg*)curr->content;
			if (arg->blank)
				ref = ft_strndup(arg->str, select->sight - 1);
		}
	}
	//ft_strcombin(&ref, &c);
	ft_dprintf(2, "========== %c\n", c);
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
		else if (buff == 65)
		{
			select->sight = (!select->sight) ? 1 : 0;
			//ft_dprintf(2, "dsjkhdjshfjdsh");
		}
		/*else if (buff > 31 && buff < 127)
		{
			if (select->sight)
				search_sight(select, buff);
		}*/
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
