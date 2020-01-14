#include "ft_select.h"

void		position_cap(t_select *select)
{
	char	*underline_cap;

	if (!(underline_cap = tgetstr("us", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(underline_cap, 1, ft_putint);
}

void		search_cap(t_select *select)
{
	char	*bold_cap;

	if (!(bold_cap = tgetstr("md", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(bold_cap, 1, ft_putint);
}

void		reset_cap(t_select *select)
{
	char	*reset_cap;

	if (!(reset_cap = tgetstr("me", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(reset_cap, 1, ft_putint);
}

void		tmp_select_cap(void)
{
	ft_dprintf(2, "%{yellow}");
	select_cap();
}

void		select_cap(void)
{
	tputs("\e[7m", 1, ft_putint);
}
