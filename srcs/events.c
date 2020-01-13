#include "ft_select.h"

static int		rank_inlst(t_dlist *lst, t_dlist *wanted)
{
	t_dlist		*curr;
	int			n;

	n = 1;
	curr = lst;
	while (curr && curr != wanted)
	{
		curr = curr->next;
		n++;
	}
	return (n);
}

void			move_arrow(t_select *select, int type)
{
	size_t		i;
	int			n;

	i = 0;
	if (!select->args)
		return ;
	if (type == KEY_DOWN)
		select->current = select->current->next;
	else if (type == KEY_UP)
		select->current = select->current->prev;
	else if (type == KEY_RIGHT)
	{
		n = rank_inlst(select->args, select->current);
		if (n + select->rows < select->nbr_args)
			while (i++ < select->rows)
				select->current = select->current->next;
	}
	else if (type == KEY_LEFT)
	{
		n = rank_inlst(select->args, select->current);
		if ((int)(n - select->rows) >= 0)
			while (i++ < select->rows)
				select->current = select->current->prev;
	}
	draw_state(select);
}

void			select_elem(t_select *select)
{
	t_arg		*arg;

	if (!select->args)
		return ;
	arg = (t_arg*)select->current->content;
	arg->select = (!arg->select) ? 1 : 0;
	select->current = select->current->next;
	draw_state(select);
}

void			delete_elem(t_select *select)
{
	t_dlist		*tmp;

	if (!select->args)
	{
		free_select(select);
		exit(EXIT_SUCCESS);
	}
	tmp = select->current;
	select->current = select->current->next;
	select->nbr_args--;
	dct_lstremove(&(select->args), tmp, delete_arg);
	draw_state(select);
}
