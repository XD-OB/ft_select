#include "ft_select.h"

static void		dt_print_inc(t_dlist *alst)
{
	t_arg		*arg;
	int			i = 0;

	if (alst)
	{
		while (++i < 8)
		{
			arg = (t_arg*)alst->content;
			ft_printf("|%s|[s%u] -> ", arg->str, arg->select);
			alst = alst->next;
		}
		ft_printf("\n");
	}
}
static void		dt_print_dec(t_dlist *alst)
{
	t_arg		*arg;
	int			i = 0;

	if (alst)
	{
		while (++i < 8)
			alst = alst->next;
		i = 0;
		while (++i < 8)
		{
			arg = (t_arg*)alst->content;
			ft_printf("|%s|[s%u] -> ", arg->str, arg->select);
			alst = alst->prev;
		}
		ft_printf("\n");
	}
}
void			print_select(t_select select)
{
	t_arg		*arg;
	int			i;

	ft_printf("nbr d'args: %d\n", select.nbr_args);
	ft_printf("----------------------\n");
	dt_print_inc(select.args);
	dt_print_dec(select.args);
	ft_printf("----------------------\n");
	arg = (t_arg*)select.current->content;
	ft_printf("point: [%s]\n", arg->str);
	ft_printf("nbr_cols: [%d]\n", select.nbr_cols);
	i = -1;
	while (++i < select.nbr_cols)
		ft_printf("[%d]", select.lens_cols[i]);
	ft_printf("\n");
}
