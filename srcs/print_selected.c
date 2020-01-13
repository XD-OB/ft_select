#include "ft_select.h"

static void		list_addnode(t_chr **alst, char *str, size_t *flag)
{
	if (*flag)
		chr_addnode(alst, " ", 0);
	else
		*flag = 1;
	chr_addnode(alst, str, 0);
}

static void		print_list(t_chr *list)
{
	t_chr		*curr;

	curr = list;
	while (curr)
	{
		ft_putstr(curr->str);
		curr = curr->next;
	}
}

void			print_selected(t_select *select)
{
	t_chr		*list;
	t_dlist		*curr;
	t_arg		*arg;
	size_t		flag;
	size_t		i;

	i = 0;
	flag = 0;
	list = NULL;
	curr = select->args;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (arg->select)
			list_addnode(&list, arg->str, &flag);
		curr = curr->next;
	}
	free_select(select);
	print_list(list);
	chr_free(&list);
	exit(EXIT_SUCCESS);
}
