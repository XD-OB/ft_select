/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:31:43 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:31:44 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (n + select->winsize.ws_row <= (int)select->nbr_args)
			while (i++ < select->winsize.ws_row)
				select->current = select->current->next;
	}
	else if (type == KEY_LEFT)
	{
		n = rank_inlst(select->args, select->current);
		if ((int)(n - select->winsize.ws_row) > 0)
			while (i++ < select->winsize.ws_row)
				select->current = select->current->prev;
	}
	draw_state(select, 0);
}

void			select_elem(t_select *select)
{
	t_arg		*arg;

	if (!select->args)
		return ;
	arg = (t_arg*)select->current->content;
	arg->nat_select = (!arg->nat_select) ? 1 : 0;
	select->current = select->current->next;
	draw_state(select, 0);
}

static void		rm_cmd(t_select *select, t_arg *arg)
{
	char		**tab;
	int			status;
	pid_t		pid;

	tab = tabstr_new(3);
	tab[0] = ft_strdup("rm");
	tab[1] = ft_strdup("-Rf");
	tab[2] = ft_strdup(arg->str);
	if ((pid = fork()) == -1)
		exit_error_fs(select, ERROR_RMCMD);
	if (pid == 0)
	{
		if (execvp("rm", tab))
			exit_error_fs(select, ERROR_RMCMD);
	}
	else
	{
		waitpid(pid, &status, 0);
		tabstr_free(&tab);
	}
}

void			delete_elem(t_select *select)
{
	struct stat	stats;
	t_dlist		*tmp;
	t_arg		*arg;

	tmp = select->current;
	if (select->real)
	{
		arg = tmp->content;
		if (stat(arg->str, &stats) != -1)
			rm_cmd(select, arg);
	}
	select->current = select->current->next;
	select->nbr_args--;
	dct_lstremove(&(select->args), tmp, delete_arg);
	if (!select->args)
	{
		free_select(select);
		exit(EXIT_SUCCESS);
	}
	draw_state(select, 1);
}
