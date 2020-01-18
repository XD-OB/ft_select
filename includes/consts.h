/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:27:41 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:28:01 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>

# define KEY_DPAGE 2117491483
# define KEY_UPAGE 2117425947
# define KEY_DEL 2117294875
# define KEY_HOME 4741915
# define KEY_RIGHT 4414235
# define KEY_LEFT 4479771
# define KEY_DOWN 4348699
# define KEY_UP 4283163
# define KEY_END 4610843
# define KEY_BSPACE 127
# define KEY_SPACE 32
# define KEY_ENTER 10
# define KEY_ESC 27
# define KEY_TAB 9

# define ERROR_SETTERM 0
# define ERROR_ATCAPDB 1
# define ERROR_TTNFDB 2
# define ERROR_ALLOC 3
# define ERROR_STDINNTERM 4
# define ERROR_GETATTR 5
# define ERROR_SETATTR 6
# define ERROR_TCAPNF 7
# define ERROR_RMCMD 8

#endif
