/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:50:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/02 15:07:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
#define FT_SELECT

# include <stdlib.h>
# include <termcap.h>
# include <libft.h>
#include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
#include <sys/stat.h>
#include <sys/param.h>

# define C_COLOR "\033[35m"		
# define O_COLOR "\033[36m"		
# define H_COLOR "\033[34m"		
# define MAKEFILE_COLOR "\033[33m"
# define DOT_COLOR "\033[32m"				
# define DEFAULT_COLOR "\033[0m"
# define A_COLOR "\033[31m"
# define REVERSE_VIDEO_COLOR "\033[7m"
# define UNDERLINED "\033[4m"

# define ENTER_KEY		10
# define ESC_KEY		27
# define SPC_KEY		32
# define STAR_KEY		42
# define MINUS_KEY		45
# define O_KEY			111
# define B_KEY			98
# define BSP_KEY		127
# define LEFT_KEY		4479771
# define UP_KEY			4283163
# define RIGHT_KEY		4414235
# define DOWN_KEY		4348699
# define DEL_KEY		2117294875L

typedef enum		e_type
{
	C_T,
	O_T,
	H_T,
	A_T,
	MAKEFILE_T,
	DOT_T,
	UNKNOWN_T
}					t_type;

typedef enum		e_dir
{
	UP_DIR,
	RIGHT_DIR,
	DOWN_DIR,
	LEFT_DIR,
	DEFAULT_DIR
}					t_dir;

typedef struct		s_file
{
	char			*name;
	struct s_file	*next;
}					t_file;

typedef struct		s_arg
{
	char			*value;
	int				is_selected;
	t_type			type;
	struct s_arg	*prev;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_select
{
	t_arg			**active_arg;
	struct termios	saved_attr;
	struct termios	attr;
	int				argc;
	char			*term_name;
	int				real_mode;
	t_arg			*args;
}					t_select;

t_select			g_select;

void				print_usage(void);
void  				column_display();
void				init_args(char **av);
void				move(t_dir direction);
int					count_columns();
int					count_max_arg_len(void);
int					ft_printnbr(int nbr);
void				signal_handler(int signo);
void				init_custom_conf();
void				reset_default_conf(void);
void				free_args(void);
void				init_signal_handlers();
void				stop_signal_handler(void);
void				delete_active_arg(void);
void				insert_arg(char *value);
void  				print_value_fd(t_arg *arg, int fd);

#endif