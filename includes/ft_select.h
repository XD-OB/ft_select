#ifndef	FT_SELECT_H
# define FT_SELECT_H

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include "consts.h"
# include "libft.h"

typedef struct		s_arg
{
	char			*str;
	int				select:1;
}					t_arg;

typedef	struct		s_select
{
	t_dlist			*args;
	t_dlist			*current;
	struct termios	old_termios;
	struct winsize	winsize;
	size_t			nbr_args;
	size_t			nbr_cols;
	int				*lens_cols;
}					t_select;

t_select			**get_aselect(void);
void				exit_error(int type);
void				exit_error_fs(t_select *select, int type);
void				init_select(t_select *select, int ac, char **av);
void				free_select(t_select *select);
void				init_term(void);
t_arg				*create_arg(char *str);
void				clear_terminal(void);
void				delete_arg(void *content, size_t size);
void				write_arg(t_select *select, t_dlist *node, int n);
int					ft_putint(int c);
void				move_arrow(t_select *select, int type);
void				print_selected(t_select *select);
void				delete_elem(t_select *select);
void				select_elem(t_select *select);
void				draw_state(t_select *select);
void				move_cursor(t_select *select, t_point p);
void				unset_ncanonic(t_select *select);
void				set_ncanonic(t_select *select);
void				print_selected(t_select *select);
t_point				cursor_pos(t_select select, int n);
void				signal_handlers(void);


void				print_select(t_select select);       ///////////

#endif
