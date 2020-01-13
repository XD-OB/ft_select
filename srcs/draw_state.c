#include "ft_select.h"

static size_t	calcul_nbrcols(size_t nbr_args, int rows)
{
	size_t		nbr_cols;

	nbr_cols = nbr_args / rows;
	if (nbr_args % rows)
		nbr_cols++;
	return (nbr_cols);
}

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
	select->nbr_cols = calcul_nbrcols(select->nbr_args, select->rows);
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
		i++;
		if (i % select->rows == 0)
			j++;
	}
}

static int		check_winsize(t_select select)
{
	size_t		line_len;
	size_t		i;

	i = 0;
	line_len = 0;
	while (i < select.nbr_cols)
		line_len += select.lens_cols[i++];
	line_len += (select.nbr_cols - 1) * 2;
	if (line_len > select.cols)
	{
		ft_putstr_fd("Small Terminal Dimension!", 2);
		return (0);
	}
	return (1);
}

static void		write_args(t_select *select)
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

void			write_empty(t_select *select)
{
	t_point		pos;
	size_t		i;
	size_t		j;
	int			n;

	i = 0;

	while (i < select->nbr_cols)
	{
		j = 0;
		while (j < select->rows)
		{
			n = (i * select->rows) + j;
			pos = cursor_pos(*select, n);
			move_cursor(select, pos);
			ft_dprintf(2, "%*s", select->lens_cols[i], " ");
			j++;
		}
		i++;
	}
}

void			draw_state(t_select *select)
{
	char		*cm_cap;

	if (select->lens_cols)
		write_empty(select);
	if (select->args)
	{
		fill_lenscols(select);
		if (!check_winsize(*select))
			return ;
		write_args(select);
	}
}
