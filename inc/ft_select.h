/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:50:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 00:21:17 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
#define FT_SELECT

# include <stdlib.h>
# include <termcap.h>
# include <libft.h>
# include <stdio.h>
# include <sys/ioctl.h>

typedef enum		e_type
{
	FILE_T,
	DIR_T,
	TEXT_T
}					t_type;

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

void				print_usage(void);
void  				column_display(t_args *args, int argc, int max_arg_len);
void				init_args(t_args **args, char **av);

#endif