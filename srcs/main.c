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
		{
			select->sight = (!select->sight) ? 1 : 0;
			if (select->len_word)
				select->len_word = 0;
		}
		else if (ft_isprint(buff))
		{
			if (select->sight)
				search_sight(select, buff);
			//else if (select->take)
			else
				search_position(select, buff);
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
