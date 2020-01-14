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
		if (arg->blink)
		{
			ref = ft_strndup(arg->str, select->sight - 1);
			break ;
		}
		curr = curr->next;
	}
	return (ref);
}

static int		update_blinks(t_select *select, char *ref)
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
			arg->blink = 1;
			found = 1;
		}
		else
			arg->blink = 0;
		curr = curr->next;
	}
	return (found);
}

void			search_sight(t_select *select, char c)
{
	char		*ref;
	int			found;

	ref = NULL;
	if (select->sight > 1)
		ref = find_ref(select);
	ft_strccombin(&ref, c);
	found = update_blinks(select, ref);
	if (found)
		select->sight++;
	else
		select->sight = 0;
	free(ref);
	draw_state(select);
}
