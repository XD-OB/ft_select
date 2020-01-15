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
	draw_state(select);
}

void			select_elem(t_select *select)
{
	t_arg		*arg;

	if (!select->args)
		return ;
	arg = (t_arg*)select->current->content;
	arg->nat_select = (!arg->nat_select) ? 1 : 0;
	select->current = select->current->next;
	draw_state(select);
}

int				check_currfx(t_arg *arg)
{
	struct stat		stats;

	if (stat(arg->str, &stats) == -1)
		return (0);
	return (1);
}

static void		exec_cmd(t_select *select, char *str)
{
	char		**tab;
	pid_t		pid;
	int			status;

	tab = tabstr_new(3);
	tab[0] = ft_strdup("rm");
	tab[1] = ft_strdup("-Rf");
	tab[2] = ft_strdup(str);
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

static void		rm_cmd(t_select *select)
{
	t_arg		*arg;

	arg = (t_arg*)select->current->content;
	exec_cmd(select, arg->str);
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
	if (select->real)
		if (check_currfx((t_arg*)tmp->content))
			rm_cmd(select);
	select->current = select->current->next;
	select->nbr_args--;
	dct_lstremove(&(select->args), tmp, delete_arg);
	draw_state(select);
}
