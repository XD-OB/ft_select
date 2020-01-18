/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:30:22 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:30:23 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void		treate_arg(t_select *select, t_dlist **first,
							t_dlist *curr, char *ref)
{
	t_arg		*arg;

	arg = (t_arg*)curr->content;
	if (!ft_strncmp(arg->str, ref, ft_strlen(ref)))
	{
		arg->search = 1;
		if (select->take)
			arg->dyn_select = 1;
		if (!*first)
			*first = curr;
	}
	else
	{
		arg->search = 0;
		if (select->take)
			arg->dyn_select = 0;
	}
}

static t_dlist	*update_searchs(t_select *select, char *ref)
{
	t_dlist		*curr;
	t_dlist		*first;
	size_t		i;

	i = 0;
	first = NULL;
	curr = select->args;
	while (i++ < select->nbr_args)
	{
		treate_arg(select, &first, curr, ref);
		curr = curr->next;
	}
	return (first);
}

void			search_engine(t_select *select, char c)
{
	t_dlist		*node;
	char		*ref;

	ref = NULL;
	if (select->len_search > 0)
		ref = find_ref(select);
	ft_strccombin(&ref, c);
	node = update_searchs(select, ref);
	if (node)
	{
		if (!select->take)
			select->current = node;
		select->len_search++;
	}
	else
	{
		if (!select->take)
			select->current = select->args;
		select->len_search = 0;
		select->take = 0;
	}
	free(ref);
	draw_state(select, 0);
}
