#include "ft_select.h"

void	exit_error(int type)
{
	char	*msg;

	msg = "error";
	if (type == ERROR_ALLOC)
		msg = "Can't Allocate Memory!";
	else if (type == ERROR_SETTERM)
		msg = "TERM is none set!";
	else if (type == ERROR_ATCAPDB)
		msg = "Fail to Access to the Termcap Database!";
	else if (type == ERROR_TTNFDB)
		msg = "Terminal type not found in the Database!";
	ft_dprintf(2, "%{red}%s%{eoc}\n", msg);
	exit(EXIT_FAILURE);
}

void	exit_error_fs(t_select *select, int type)
{
	char	*msg;

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
	ft_dprintf(2, "%{red}%s%{eoc}\n", msg);
	free_select(select);
	exit(EXIT_FAILURE);
}
