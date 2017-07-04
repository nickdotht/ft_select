/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:50:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/04 07:19:09 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdlib.h>
# include <termcap.h>
# include <libft.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <ftw.h>
# include <unistd.h>
# include <sys/param.h>

/*
** Predefined color/attribute codes
*/

# define C_COLOR				"\033[35m"
# define O_COLOR				"\033[36m"
# define H_COLOR				"\033[34m"
# define MAKEFILE_COLOR			"\033[33m"
# define DOT_COLOR				"\033[32m"
# define DEFAULT_COLOR			"\033[0m"
# define A_COLOR				"\033[31m"
# define REVERSE_VIDEO_COLOR	"\033[7m"
# define UNDERLINED				"\033[4m"

/*
** Supported keys during program execution
*/

# define ENTER_KEY				10
# define ESC_KEY				27
# define SPC_KEY				32
# define STAR_KEY				42
# define MINUS_KEY				45
# define O_KEY					111
# define B_KEY					98
# define BSP_KEY				127
# define LEFT_KEY				4479771
# define UP_KEY					4283163
# define RIGHT_KEY				4414235
# define DOWN_KEY				4348699
# define DEL_KEY				2117294875L

/*
** File types supported by the program, will add more
**
** C_T 			- .c
** O_T 			- .o
** H_T 			- .h
** A_T 			- .a
** MAKEFILE_T 	- Makefile
** DOT_T 		- dot files (.gitignore, .vimrc)
** UNKNOWN_T 	- unknown or unsupported type
*/

typedef enum					e_type
{
	C_T,
	O_T,
	H_T,
	A_T,
	MAKEFILE_T,
	DOT_T,
	UNKNOWN_T
}								t_type;

/*
** Cursor directions in the arguments/files browser
**
** DEFAULT_DIR is for unknown/unsupported keys
*/

typedef enum					e_dir
{
	UP_DIR,
	RIGHT_DIR,
	DOWN_DIR,
	LEFT_DIR,
	DEFAULT_DIR
}								t_dir;

/*
** The list of arguments to display and edit
**
** value 		- The argument value
** is_selected 	- A boolean to know if the current argument is selected or not
** type			- The type of the current argument
** prev			- The previous argument
** next			- The next argument
*/

typedef struct					s_arg
{
	char						*value;
	int							is_selected;
	t_type						type;
	struct s_arg				*prev;
	struct s_arg				*next;
}								t_arg;

/*
** A struct that holds any information we might need about the arguments list
**
** active_arg		- The currently active argument
** old_attr			- The old attributes before we apply our own
** attr				- Our custom attributes
** argc				- The arguments count
** term_name		- The terminal name from the environment
** real_mode		- A boolean to know if the program should really delete
**					files from the system or not
** args				- The arguments list
** selected_count 	- The amount of selected arguments for use when printing
*/

typedef struct					s_select
{
	t_arg						**active_arg;
	struct termios				old_attr;
	struct termios				attr;
	int							argc;
	char						*term_name;
	int							real_mode;
	t_arg						*args;
	int							selected_count;
}								t_select;

/*
** The global variable that will be used during the whole execution
**
** I'm using a global variable so I can be able to free the memory once
** the program gets killed, there are no other methods of doing this. Unless we
** don't use signals anymore, but for this project, I wasn't allowed to use
** anything else.
*/

t_select						g_select;

/*
** src/actions.c
*/

void							move(t_dir direction);

/*
** src/column_display.c
*/

void							column_display();
int								count_columns();
void							print_value_fd(t_arg *arg, int fd);

/*
** src/init_args.c
*/

void							init_args(char **av);
void							free_args(void);
void							delete_active_arg(void);
void							insert_arg(char *value);

/*
** src/main.c
*/

void							init_custom_conf();
void							init_signal_handlers();

/*
** src/print_usage.c
*/

void							print_usage(void);

/*
** src/signal_handler.c
*/

void							signal_handler(int signo);
void							stop_signal_handler(void);

/*
** src/utils.c
*/

void							validate_flag(char *arg);
void							on_key_press(void);

/*
** src/utils2.c
*/

int								count_max_arg_len(void);
int								ft_printnbr(int nbr);
void							reset_default_conf(void);
void							toggle_all_args(long key);

/*
** src/utils3.c
*/

void							system_delete_arg(char *path);

#endif
