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

void			write_emptys(t_select *select)
{
	char			*str;
	size_t			len;

	move_cursor(select, pt_new(0, 0));
	len = select->winsize.ws_row * select->winsize.ws_col;
	str = ft_strcnew(len, ' ');
	write(2, str, len);
	free(str);
}

void			draw_state(t_select *select)
{
	write_emptys(select);
	if (select->args)
	{
		fill_lenscols(select);
		if (!check_winsize(select))
			return ;
		write_args(select);
	}
}
