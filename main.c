#include "ft_select.h"

void	exit_error(char *msg)
{
	ft_dprintf(2, "%{red}%s%{eoc}\n", msg);
	exit(EXIT_FAILURE);
}

void	exit_error_fs(t_select *select, char *msg)
{
	free_select(select);
	ft_dprintf(2, "%{red}%s%{eoc}\n", msg);
	exit(EXIT_FAILURE);
}

t_arg	*create_arg(char *str)
{
	t_arg	*arg;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))))
		exit_error("Can't Allocate Memory");
	arg->str = ft_strdup(str);
	arg->select = 0;
	return (arg);
}

void	set_stdin_mode(t_select *select)
{
	struct termios		new_termios;

	if (tcgetattr(STDIN_FILENO, &new_termios))
		exit_error_fs(select, "Error While Getting Parameters associated with the terminal!");
	new_termios.c_lflag &= ~(ICANON);
	new_termios.c_lflag &= ~(ECHO);
	new_termios.c_cc[VMIN] = 1;
	new_termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &new_termios))
		exit_error_fs(select, "Error While Setting Parameters associated with the terminal!");
}

int				ft_putint(int c)
{
	write(2, &c, 1);
	return (0);
}

void		clear_terminal(void)
{
	char		*clear_cap;

	clear_cap = tgetstr("cl", NULL);
	tputs(clear_cap, 1, ft_putint);
}

static size_t	calcul_nbrcols(size_t nbr_args, int rows)
{
	size_t		nbr_cols;

	nbr_cols = nbr_args / rows;
	if (nbr_args % rows)
		nbr_cols++;
	return (nbr_cols);
}

void			fill_lenscols(t_select *select)
{
	t_dlist		*curr;
	t_arg		*arg;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	curr = select->args;
	select->nbr_cols = calcul_nbrcols(select->nbr_args, select->rows);
	if (!(select->lens_cols =
			(int*)malloc(sizeof(int) * select->nbr_cols)))
		exit_error_fs(select, "Can't Allocate Memory!");
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

int				check_winsize(t_select select)
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

static t_point	cursor_pos(t_select select, int n)
{
	t_point		pos;
	int			tmp;
	int			i;

	pos.x = 0;
	pos.y = n % select.rows;
	tmp = n / select.rows;
	i = -1;
	while (++i < tmp)
		pos.x += select.lens_cols[i];
	return (pos);
}

static void		reset_cap(t_select *select)
{
	char		*reset_cap;

	if (!(reset_cap = tgetstr("me", NULL)))
		exit_error_fs(select, "Terminal capacity not found!");
	tputs(reset_cap, 1, ft_putint);
}

static void		position_cap(t_select *select)
{
	char		*underline_cap;

	if (!(underline_cap = tgetstr("us", NULL)))
		exit_error_fs(select, "Terminal capacity not found!");
	tputs(underline_cap, 1, ft_putint);
}
static void		select_cap(t_select *select)
{
	tputs("\e[7m", 1, ft_putint);
}

static void		write_arg(t_select *select, t_dlist *node, int n)
{
	char		*cm_cap;
	t_arg		*arg;
	t_point		pos;

	arg = (t_arg*)node->content;
	if (!(cm_cap = tgetstr("cm", NULL)))
		exit_error_fs(select, "Terminal capacity not found!");
	pos = cursor_pos(*select, n);
	tputs(tgoto(cm_cap, pos.x, pos.y), 1, ft_putint);
	if (node == select->current)
		position_cap(select);
	if (arg->select)
		select_cap(select);
	ft_putstr_fd(arg->str, 2);
	reset_cap(select);
}

void		write_args(t_select *select)
{
	t_dlist	*curr;
	int		n;

	if (select->args)
	{
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
}

void	draw_state(t_select *select)
{
	clear_terminal();
	fill_lenscols(select);
	if (!check_winsize(*select))
		return ;
	write_args(select);
}

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

static void		move_arrow(t_select *select, int type)
{
	int			n;
	int			i;

	if (type == KEY_DOWN)
		select->current = select->current->next;
	else if (type == KEY_UP)
		select->current = select->current->prev;
	else if (type == KEY_RIGHT)
	{
		i = 0;
		n = rank_inlst(select->args, select->current);
		if (n + select->rows < select->nbr_args)
			while (i++ < select->rows)
				select->current = select->current->next;
	}
	else if (type == KEY_LEFT)
	{
		i = 0;
		n = rank_inlst(select->args, select->current);
		if (n - select->rows >= 0)
			while (i++ < select->rows)
				select->current = select->current->prev;
	}
	draw_state(select);
}

void		select_elem(t_select *select)
{
	t_arg	*arg;

	arg = (t_arg*)select->current->content;
	arg->select = (!arg->select) ? 1 : 0;
	select->current = select->current->next;
	draw_state(select);
}

void		print_selected(t_select *select)
{
	t_dlist		*curr;
	t_arg		*arg;
	size_t		flag;
	size_t		i;

	flag = 0;
	curr = select->args;
	i = 0;
	while (i++ < select->nbr_args)
	{
		arg = (t_arg*)curr->content;
		if (flag)
			ft_putstr_fd(" ", 2);
		else
			flag = 1;
		if (arg->select)
			ft_putstr_fd(arg->str, 2);
		curr = curr->next;
	}
	free_select(select);
	exit(EXIT_SUCCESS);
}

void	launch_select(t_select *select)
{
	int		buff;

	buff = 0;
	draw_state(select);
	while (read(STDIN_FILENO, &buff, 4) != 0)
	{
		if (buff == KEY_ESC)
			break ;
		else if (buff == KEY_RIGHT)
			move_arrow(select, KEY_RIGHT);
		else if (buff == KEY_LEFT)
			move_arrow(select, KEY_LEFT);
		else if (buff == KEY_DOWN)
			move_arrow(select, KEY_DOWN);
		else if (buff == KEY_UP)
			move_arrow(select, KEY_UP);
		else if (buff == KEY_SPACE)
			select_elem(select);
		//else if (buff == KEY_DEL || buff == KEY_BSPACE)
		//	delete_elem(select);
		else if (buff == KEY_ENTER)
			print_selected(select);
		buff = 0;
	}
}

int		main(int ac, char **av)
{
	t_select	select;

	init_term();
	init_select(&select, ac, av);
	set_stdin_mode(&select);
	launch_select(&select);
	//print_select(select);			//////////
	free_select(&select);
	return (EXIT_SUCCESS);
}
