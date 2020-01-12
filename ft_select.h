#ifndef	FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
# include <termcap.h>
# include <termios.h>

# define KEY_RIGHT 4414235
# define KEY_LEFT 4479771
# define KEY_DOWN 4348699
# define KEY_UP 4283163
# define KEY_BSPACE 8
# define KEY_SPACE 32
# define KEY_ENTER 10
# define KEY_DEL 127
# define KEY_ESC 27

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
	size_t			nbr_args;
	size_t			nbr_cols;
	int				*lens_cols;
	int				rows;
	int				cols;
}					t_select;

void				exit_error(char *msg);
void				exit_error_fs(t_select* select, char *msg);
void				init_select(t_select *select, int ac, char **av);
void				free_select(t_select *select);
void				init_term(void);
t_arg				*create_arg(char *str);
void				clear_terminal(void);

void				print_select(t_select select);       ///////////

#endif
