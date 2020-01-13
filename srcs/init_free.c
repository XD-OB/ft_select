#include "ft_select.h"

void			init_term(void)
{
	char		*term_type;
	int			ret;

	term_type = getenv("TERM");
	if (!term_type)
		exit_error(ERROR_SETTERM);
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		exit_error(ERROR_ATCAPDB);
	if (ret == 0)
		exit_error(ERROR_TTNFDB);
}

static void		save_old_termios(t_select *select)
{
	if (isatty(STDIN_FILENO) != 1)
		exit_error_fs(select, ERROR_STDINNTERM);
	tcgetattr(STDIN_FILENO, &(select->old_termios));
}

void			init_select(t_select *select, int ac, char **av)
{
	t_dlist		*node;
	t_arg		*arg;
	int			i;

	select->args = NULL;
	select->lens_cols = NULL;
	select->nbr_cols = 0;
	select->nbr_args = ac - 1;
	select->winsize.ws_row = tgetnum("li");
	select->winsize.ws_col = tgetnum("co");
	i = 0;
	while (++i < ac)
	{
		arg = create_arg(av[i]);
		node = dct_lstnew_sm(arg, sizeof(t_arg*));
		dct_lstadd_last(&(select->args), node);
	}
	select->current = select->args;
	save_old_termios(select);
}

void		delete_arg(void *content, size_t size)
{
	t_arg		*arg;

	(void)size;
	arg = (t_arg*)content;
	free(arg->str);
	free(arg);
}

void			free_select(t_select *select)
{
	if (select->lens_cols)
		free(select->lens_cols);
	if (select->args)
		dct_lstdel(&(select->args), delete_arg);
	unset_ncanonic(select);
}
