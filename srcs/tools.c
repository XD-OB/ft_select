#include "ft_select.h"

t_arg				*create_arg(char *str)
{
	t_arg			*arg;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))))
		exit_error(ERROR_ALLOC);
	arg->str = ft_strdup(str);
	arg->dyn_select = 0;
	arg->nat_select = 0;
	arg->search = 0;
	return (arg);
}

void				delete_arg(void *content, size_t size)
{
	t_arg			*arg;

	(void)size;
	arg = (t_arg*)content;
	free(arg->str);
	free(arg);
}

size_t				calcul_nbrcols(size_t nbr_args, int rows)
{
	size_t			nbr_cols;

	nbr_cols = nbr_args / rows;
	if (nbr_args % rows)
		nbr_cols++;
	return (nbr_cols);
}

t_select			**get_aselect(void)
{
	static t_select	*select = NULL;

	return (&select);
}

int					ft_putint(int c)
{
	write(2, &c, 1);
	return (1);
}
