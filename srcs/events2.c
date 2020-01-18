/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:31:38 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:31:40 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_dlist		*prev_result(t_select *select)
{
	t_dlist			*curr;
	t_arg			*arg;
	size_t			i;

	i = 1;
	curr = select->current->prev;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (arg->search)
			return (curr);
		curr = curr->prev;
	}
	return (NULL);
}

static t_dlist		*next_result(t_select *select)
{
	t_dlist			*curr;
	t_arg			*arg;
	size_t			i;

	i = 1;
	curr = select->current->next;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (arg->search)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void				move_search(t_select *select, int type)
{
	t_dlist			*result;
	size_t			i;

	i = 1;
	if (type == KEY_DPAGE)
		result = next_result(select);
	else
		result = prev_result(select);
	if (result)
		select->current = result;
	draw_state(select, 0);
}

void				empty_search(t_select *select)
{
	t_dlist			*curr;
	t_arg			*arg;
	size_t			i;

	i = 0;
	select->len_search = 0;
	select->current = select->args;
	curr = select->current;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		arg->search = 0;
		arg->dyn_select = 0;
		curr = curr->next;
	}
	draw_state(select, 0);
}
