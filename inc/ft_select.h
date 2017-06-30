/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:50:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 02:01:20 by jrameau          ###   ########.fr       */
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

# define C_COLOR "\033[35m"		
# define O_COLOR "\033[36m"		
# define H_COLOR "\033[34m"		
# define MAKEFILE_COLOR "\033[33m"
# define DOT_COLOR "\033[32m"				
# define A_COLOR "\033[31m"

# define ENTER_KEY		10
# define ESC_KEY		27
# define SPC_KEY		32
# define STAR_KEY		42
# define MINUS_KEY		45
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

typedef struct		s_args
{
	char			*value;
	int				is_selected;
	t_type			type;
	struct s_args	*prev;
	struct s_args	*next;
}					t_args;

typedef struct		s_select
{
	t_args			**active_arg;
	struct termios	saved_attr;
	int				args_per_row;
	int				argc;
	char			*term_name;
	t_args			*args;
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
void				remove_arg(void);

#endif