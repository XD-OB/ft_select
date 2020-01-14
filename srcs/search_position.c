#include "ft_select.h"

static t_dlist	*first_match(t_select *select, char *ref)
{
	t_dlist		*curr;
	t_arg		*arg;
	size_t		len_ref;
	size_t		i;

	i = 0;
	curr = select->args;
	len_ref = ft_strlen(ref);
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (!ft_strncmp(arg->str, ref, len_ref))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static char		*find_ref_2(t_select *select)
{
	t_arg		*arg;
	char		*ref;

	ref = NULL;
	if (select->len_word)
	{
		arg = (t_arg*)select->current->content;
		ref = ft_strndup(arg->str, select->len_word);
	}
	return (ref);
}

void			search_position(t_select *select, char c)
{
	t_dlist		*curr;
	char		*ref;
	int			found;

	found = 0;
	ref = NULL;
	ref = find_ref_2(select);
	ft_strccombin(&ref, c);
	curr = first_match(select, ref);
	if (curr)
	{
		select->current = curr;
		select->len_word++;
	}
	else
	{
		select->current = select->args;
		select->len_word = 0;
	}
	free(ref);
	draw_state(select);
}
