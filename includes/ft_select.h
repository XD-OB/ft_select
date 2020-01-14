#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include "consts.h"
# include "libft.h"

/*
**	nat: natural
**	dyn: dynamic
*/

typedef struct		s_arg
{
	char			*str;
	int				dyn_select:1;
	int				nat_select:1;
	int				search:1;
}					t_arg;

typedef	struct		s_select
{
	t_dlist			*args;
	t_dlist			*current;
	struct termios	old_termios;
	struct winsize	winsize;
	size_t			nbr_args;
	size_t			nbr_cols;
	size_t			len_search;
	int				*lens_cols;
	int				take:1;
}					t_select;

void				init_term(void);
t_select			**get_aselect(void);
void				exit_error(int type);
void				exit_error_fs(t_select *select, int type);
void				init_select(t_select *select, int ac, char **av);
void				free_select(t_select *select);
t_arg				*create_arg(char *str);
void				write_args(t_select *select);
void				launch_select(t_select *select);
void				delete_arg(void *content, size_t size);
void				move_arrow(t_select *select, int type);
void				print_selected(t_select *select);
void				delete_elem(t_select *select);
void				select_elem(t_select *select);
void				draw_state(t_select *select);
void				unset_ncanonic(t_select *select);
void				set_ncanonic(t_select *select);
void				print_selected(t_select *select);
void				move_cursor(t_select *select, t_point p);
t_point				cursor_pos(t_select select, int n);
void				signal_handlers(void);
void				search_engine(t_select *select, char c);
void				position_cap(t_select *select);
void				search_cap(t_select *select);
void				reset_cap(t_select *select);
void				tmp_select_cap(void);
void				select_cap(void);
int					ft_putint(int c);

void				print_select(t_select select);       ///////////

#endif
