/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:39:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/02 01:42:04 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/*
** Returns either the current width or height of the terminal depending on the
** value of 'w_or_h'
**
** @param     w_or_h    1 for width, 0 for height
** @return    The value of the width/height
*/

int		get_term_size(int w_or_h)
{
		struct  winsize w;

		ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
		return ((w_or_h) ? w.ws_col : w.ws_row);
}

/*
** Counts the maximum amount of columns possible on the current terminal size
**
** @param     N/A
** @return    The total amount of columns possible
*/

int		count_columns(void)
{
	int cols;

	cols = get_term_size(1) / (count_max_arg_len() + 1);
		if (!cols)
			cols = 1;
		if ((count_max_arg_len() + 1) * g_select.argc < get_term_size(1))
			cols = g_select.argc;
		return cols;
}

/*
** Prints the value of the passed in argument in the desired fd
** 
** Depending on the type of the argument, we print a specific color.
**
** @param     arg     The argument to print the value of
** @param     fd      The file descriptor in which to print to
** @return    N/A
*/

void  print_value_fd(t_arg *arg, int fd)
{
	if (arg->type == C_T)
		ft_putstr_fd(C_COLOR, fd);
	else if (arg->type == O_T)
		ft_putstr_fd(O_COLOR, fd);
	else if (arg->type == H_T)
		ft_putstr_fd(H_COLOR, fd);
	else if (arg->type == MAKEFILE_T)
		ft_putstr_fd(MAKEFILE_COLOR, fd);
	else if (arg->type == DOT_T)
		ft_putstr_fd(DOT_COLOR, fd);
	else if (arg->type == A_T)
		ft_putstr_fd(A_COLOR, fd);
	ft_putstr_fd(arg->value, fd);
	ft_putstr_fd(DEFAULT_COLOR, STDIN_FILENO);
}

/*
** Displays the list of arguments on the screen
**
** Depending on the type of the value and the state in which it is, it will:
** - underline the text if it's the active value
** - reverse video the text if the value is selected
** and then it prints the value
**
** @param     args    The list of arguments
** @param     first   The first element of the list, passed as an argument to
**                    save lines in the function (25 lines limit)
** @param     rows    The amount of rows possible
** @param     cols    The amount of columns possible
** @return    N/A
*/

void  display_args(t_arg *args, t_arg *first, int rows, int cols)
{
	int   i;
	int   j;
	int   str_len;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (args == (*g_select.active_arg))
				ft_putstr_fd(UNDERLINED, STDIN_FILENO);
			if (args->is_selected)
				ft_putstr_fd(REVERSE_VIDEO_COLOR, STDIN_FILENO);
			print_value_fd(args, STDIN_FILENO);
			str_len = ft_strlen(args->value);
			while (str_len++ <= count_max_arg_len())
				ft_putstr_fd(" ", STDIN_FILENO);
			if (args->next == first)
				break;
			args = args->next;
		}
		ft_putstr_fd("\n", STDIN_FILENO);
	}
}

/*
** Displays the columns of values
** 
** If it cannot fit at least 1 column on the screen, it displays
** a blank screen
** If it can, it first clears the whole screen, calculates rows and columns.
** It also displays a blank screen if the height of the window is not long
** enough. Then it displays thre list of arguments.
** 
** @param     N/A
** @return    N/A
*/

void    column_display()
{
		int     cols;
		int     rows;

		if (!g_select.args || count_max_arg_len() > get_term_size(1))
			return ;
		tputs(tgetstr("cl", NULL), 1, ft_printnbr);
		cols = count_columns();
		rows = g_select.argc / cols;
		if (rows > get_term_size(0))
			return ;
		if (g_select.argc % cols)
			++rows;
		display_args(g_select.args, g_select.args, rows, cols);
}