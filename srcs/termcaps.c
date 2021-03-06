/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:28:51 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:28:57 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		position_cap(t_select *select)
{
	char	*underline_cap;

	if (!(underline_cap = tgetstr("us", NULL)))
		exit_error_fs(select, ERROR_TCAPNF);
	tputs(underline_cap, 1, ft_putint);
}

void		bold_cap(t_select *select)
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

void		select_cap(void)
{
	tputs("\e[7m", 1, ft_putint);
}
