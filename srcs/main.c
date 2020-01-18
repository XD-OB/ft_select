#include "ft_select.h"

static int		wrong_args(t_select *select, int ac, char **av)
{
	if (ac < 2)
		return (1);
	if (!ft_strcmp(av[1], "--real") || !ft_strcmp(av[1], "-r"))
	{
		if (ac == 2)
			return (1);
		select->real = 1;
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_select	**aselect;
	t_select	select;

	aselect = get_aselect();
	*aselect = &select;
	if (wrong_args(&select, ac, av))
		exit_usage();
	init_term();
	signal_handlers();
	init_select(&select, ac, av);
	set_ncanonic(&select);
	launch_select(&select);
	free_select(&select);
	return (EXIT_SUCCESS);
}
