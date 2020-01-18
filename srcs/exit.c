/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:27:11 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:46:08 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			exit_usage(void)
{
	ft_dprintf(2, "%{red}Usage:%{eoc} ./ft_select [-rh] (arg1 ...)\n");
	ft_dprintf(2, "   real mode: --real -r : Delete the erased files!\n");
	ft_dprintf(2, "   real mode: --help -h : Show the Manual!\n");
	exit(EXIT_FAILURE);
}

void			exit_help(void)
{
	ft_dprintf(2, "\n        * Manual *\n");
	ft_dprintf(2, "%{blue}-----------------------------------");
	ft_dprintf(2, "------------------------%{eoc}\n");
	ft_dprintf(2, "%{GREEN}TAB   %{eoc}    : (%{cyan}ON %{eoc}) ");
	ft_dprintf(2, "Activate selection with dynamic search.\n       ");
	ft_dprintf(2, "     (%{cyan}OFF%{eoc}) End and select the results.\n");
	ft_dprintf(2, "%{GREEN}HOME  %{eoc}    : ");
	ft_dprintf(2, "Clear the search results.\n");
	ft_dprintf(2, "%{GREEN}END   %{eoc}    : ");
	ft_dprintf(2, "Enter in a folder and load his contents.\n");
	ft_dprintf(2, "%{GREEN}SPACE %{eoc}    : Select Element.\n");
	ft_dprintf(2, "%{GREEN}UP PAGE%{eoc}   : ");
	ft_dprintf(2, "Put the cursor in the prev search result.\n");
	ft_dprintf(2, "%{GREEN}DOWN PAGE%{eoc} : ");
	ft_dprintf(2, "Put the cursor in the next search result.\n");
	ft_dprintf(2, "%{GREEN}BACK SPACE%{eoc}: ");
	ft_dprintf(2, "Remove the element.\n");
	ft_dprintf(2, "%{GREEN}DELETE    %{eoc}: ");
	ft_dprintf(2, "Remove the element.\n");
	ft_dprintf(2, "%{GREEN}ARROWS%{eoc}    : Move the cursor in the list.\n");
	ft_dprintf(2, "%{GREEN}ENTER %{eoc}    : Exit and print the results.\n");
	ft_dprintf(2, "%{GREEN}EXIT  %{eoc}    : Exit and lose the results.\n");
	ft_dprintf(2, "%{blue}-----------------------------------");
	ft_dprintf(2, "------------------------%{eoc}\n");
	exit(EXIT_SUCCESS);
}

void			exit_error(int type)
{
	char		*msg;

	msg = "error";
	if (type == ERROR_ALLOC)
		msg = "Can't Allocate Memory!";
	else if (type == ERROR_SETTERM)
		msg = "TERM is not set!";
	else if (type == ERROR_ATCAPDB)
		msg = "Fail to Access to the Termcap Database!";
	else if (type == ERROR_TTNFDB)
		msg = "Terminal type not found in the Database!";
	ft_dprintf(2, "%{red}%s%{eoc}\n", msg);
	exit(EXIT_FAILURE);
}

void			exit_error_fs(t_select *select, int type)
{
	char		*msg;

	msg = "error";
	move_cursor(select, pt_new(0, 0));
	if (type == ERROR_ALLOC)
		msg = "Can't Allocate Memory!";
	else if (type == ERROR_STDINNTERM)
		msg = "STDIN fd refer to file other than terminal!";
	else if (type == ERROR_GETATTR)
		msg = "Error To Get Params associated with the terminal!";
	else if (type == ERROR_SETATTR)
		msg = "Error To Set Params associated with the terminal!";
	else if (type == ERROR_TCAPNF)
		msg = "Terminal Capacity not found!";
	else if (type == ERROR_RMCMD)
		msg = "Problem to Execute the rm command!";
	free_select(select);
	ft_dprintf(2, "%{red}%s%{eoc}\n", msg);
	exit(EXIT_FAILURE);
}
