/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:50:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 11:29:14 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
#define FT_SELECT

# include <stdlib.h>
# include <termcap.h>
# include <libft.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>

typedef enum		e_type
{
	FILE_T,
	DIR_T,
	TEXT_T
}					t_type;

typedef enum		e_key
{
	UP_K,
	RIGHT_K,
	DOWN_K,
	LEFT_K,
	DEFAULT_K
}					t_key;

typedef struct		s_args
{
	char			*value;
	int				is_active;
	int				is_selected;
	// t_type			type; / BONUS
	struct s_args	*top;
	struct s_args	*right;
	struct s_args	*bottom;
	struct s_args	*left;
}					t_args;

t_args				*g_args;
struct termios		g_saved_attr;


void				print_usage(void);
void  				column_display(int argc, int max_arg_len);
void				init_args(char **av);
void				move_down();
void				move_up();
void				move_right();
void				move_left();

#endif