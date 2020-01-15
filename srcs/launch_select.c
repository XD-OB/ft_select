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
