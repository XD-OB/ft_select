#include "ft_select.h"

static char		*find_ref(t_select *select)
{
	t_dlist		*curr;
	t_arg		*arg;
	char		*ref;
	size_t		i;

	i = 0;
	ref = NULL;
	curr = select->args;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (arg->search)
		{
			ref = ft_strndup(arg->str, select->len_search);
			break ;
		}
		curr = curr->next;
	}
	return (ref);
}

static int		update_searchs(t_select *select, char *ref)
{
	t_dlist		*curr;
	t_arg		*arg;
	int			found;
	size_t		len_ref;
	size_t		i;

	i = 0;
	found = 0;
	len_ref = ft_strlen(ref);
	curr = select->args;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (!ft_strncmp(arg->str, ref, len_ref))
		{
			arg->search = 1;
			arg->dyn_select = 1;
			found = 1;
		}
		else
		{
			arg->search = 0;
			arg->dyn_select = 0;
		}
		curr = curr->next;
	}
	return (found);
}

void			search_take(t_select *select, char c)
{
	char		*ref;
	int			found;

	ref = NULL;
	if (select->len_search > 0)
		ref = find_ref(select);
	ft_strccombin(&ref, c);
	found = update_searchs(select, ref);
	if (found)
		select->len_search++;
	else
	{
		select->len_search = 0;
		select->take = 0;
	}
	free(ref);
	draw_state(select);
}
