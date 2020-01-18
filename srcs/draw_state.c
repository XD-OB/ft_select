#include "ft_select.h"

static void		fill_lenscols(t_select *select)
{
	t_dlist		*curr;
	t_arg		*arg;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	curr = select->args;
	if (select->lens_cols)
		free(select->lens_cols);
	select->nbr_cols =
		calcul_nbrcols(select->nbr_args, select->winsize.ws_row);
	if (!(select->lens_cols =
				(int*)malloc(sizeof(int) * select->nbr_cols)))
		exit_error_fs(select, ERROR_ALLOC);
	tabint_reset(select->lens_cols, select->nbr_cols, 0);
	while (i < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		select->lens_cols[j] =
			ft_max(select->lens_cols[j], ft_strlen(arg->str));
		curr = curr->next;
		if (++i % select->winsize.ws_row == 0)
			j++;
	}
}

static int		check_winsize(t_select *select)
{
	size_t		line_len;
	size_t		i;

	i = 0;
	line_len = 0;
	while (i < select->nbr_cols)
		line_len += select->lens_cols[i++];
	line_len += (select->nbr_cols - 1) * 2;
	if (line_len > select->winsize.ws_col)
		return (0);
	return (1);
}

static void		write_emptys(t_select *select)
{
	char		*delline_cap;
	char		*str;
	size_t		len;
	t_point		p;

	p = pt_new(0, 0);
	delline_cap = tgetstr("ce", NULL);
	if (delline_cap)
	{
		while (p.y < select->winsize.ws_row)
		{
			move_cursor(select, p);
			tputs(delline_cap, 1, ft_putint);
			p.y++;
		}
	}
	else
	{
		move_cursor(select, p);
		len = select->winsize.ws_row * select->winsize.ws_col;
		str = ft_strcnew(len, ' ');
		write(2, str, len);
		free(str);
	}
}

void			write_args(t_select *select)
{
	t_dlist		*curr;
	int			n;

	n = 0;
	curr = select->args;
	write_arg(select, curr, n++);
	curr = curr->next;
	while (curr != select->args)
	{
		write_arg(select, curr, n);
		curr = curr->next;
		n++;
	}
}

void			draw_state(t_select *select, int del)
{
	if (del)
		write_emptys(select);
	if (select->args)
	{
		fill_lenscols(select);
		if (!check_winsize(select))
			return ;
		write_args(select);
	}
}
