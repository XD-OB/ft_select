/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:30:37 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:30:38 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		to_natural(t_select *select)
{
	t_dlist		*curr;
	t_arg		*arg;
	size_t		i;

	i = 0;
	curr = select->args;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (arg->dyn_select)
		{
			arg->nat_select = (!arg->nat_select) ? 1 : 0;
			arg->dyn_select = 0;
			arg->search = 0;
		}
		curr = curr->next;
	}
}

static void		sound_terminal(void)
{
	char		*sound_cap;

	sound_cap = tgetstr("bl", NULL);
	if (sound_cap)
		tputs(sound_cap, 1, ft_putint);
}

void			press_tab(t_select *select)
{
	sound_terminal();
	if (select->take)
	{
		select->take = 0;
		to_natural(select);
	}
	else
		select->take = 1;
	select->len_search = 0;
	draw_state(select, 0);
}
