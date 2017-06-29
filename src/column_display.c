/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:39:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 19:08:13 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int		get_term_size(int w_or_h)
{
    struct  winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return ((w_or_h) ? w.ws_col : w.ws_row);
}

int		count_columns()
{
	int cols;

	cols = get_term_size(1) / (count_max_arg_len() + 1);
    if (!cols)
      cols = 1;
    if ((count_max_arg_len() + 1) * g_select.argc < get_term_size(1))
      cols = g_select.argc;
  	return cols;
}

void	display_args(t_args *args, t_args *first, int rows, int cols)
{
	int		i;
	int		j;
  	int		str_len;

	i = -1;
    while (++i < rows)
    {
      j = -1;
      while (++j < cols)
      {
      	if (args == (*g_select.active_arg))
      		ft_putstr("\033[4;m");
        ft_putstr(args->value);
      	ft_putstr("\033[0m");
        str_len = ft_strlen(args->value);
        while (str_len++ <= count_max_arg_len())
        	ft_putstr(" ");
        if (args->next == first)
        	break;
        args = args->next;
      }
      ft_putstr("\n");
    }
}

void    column_display()
{
    int     cols;
    int     rows;

    if (!g_select.args || count_max_arg_len() > get_term_size(1))
    	return ;
    cols = count_columns();
    rows = g_select.argc / cols;
    if (rows > get_term_size(0))
    	return ;
    if (g_select.argc % cols)
      ++rows;
    display_args(g_select.args, g_select.args, rows, cols);
}