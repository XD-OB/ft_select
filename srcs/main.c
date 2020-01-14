#include "ft_select.h"

int		main(int ac, char **av)
{
	t_select	**aselect;
	t_select	select;

	aselect = get_aselect();
	*aselect = &select;
	init_term();
	signal_handlers();
	init_select(&select, ac, av);
	set_ncanonic(&select);
	launch_select(&select);
	free_select(&select);
	return (EXIT_SUCCESS);
}
