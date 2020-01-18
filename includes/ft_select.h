/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:28:07 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 07:30:10 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

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
	int				real:1;
	int				take:1;
}					t_select;

void				init_term(void);
t_select			**get_aselect(void);
void				exit_help(void);
void				exit_usage(void);
void				exit_error(int type);
void				exit_error_fs(t_select *select, int type);
void				signal_handlers(void);
void				init_select(t_select *select, int ac, char **av);
void				free_select(t_select *select);
t_arg				*create_arg(char *str);
void				write_arg(t_select *select, t_dlist *node, int n);
void				launch_select(t_select *select);
void				press_tab(t_select *select);
void				fix_prevpath(char **path);
void				delete_arg(void *content, size_t size);
void				move_arrow(t_select *select, int type);
void				move_search(t_select *select, int type);
void				print_selected(t_select *select);
void				empty_search(t_select *select);
void				delete_elem(t_select *select);
void				select_elem(t_select *select);
void				draw_state(t_select *select, int del);
void				set_ncanonic(t_select *select);
void				unset_ncanonic(t_select *select);
void				print_selected(t_select *select);
t_point				cursor_pos(t_select select, int n);
void				move_cursor(t_select *select, t_point p);
void				search_engine(t_select *select, char c);
size_t				calcul_nbrcols(size_t nbr_args, int rows);
void				navigate_rep(t_select *select);
void				position_cap(t_select *select);
void				reset_cap(t_select *select);
void				bold_cap(t_select *select);
void				select_cap(void);
int					ft_putint(int c);

#endif
