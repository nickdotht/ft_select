/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:39:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 16:48:24 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void    column_display(int argc, int max_arg_len)
{
    struct  winsize w;
    int     cols;
    int     rows;
    int     term_width;
    int     term_height;
    int     i;
    int		j;
  	int		str_len;
  	t_args	*args;
  	t_args	*first;

    if (!g_select.args)
    	return ;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    term_width = w.ws_col;
    term_height = w.ws_row;
    if (max_arg_len > term_width)
    	return ;
    cols = term_width / (max_arg_len + 1);
    if (!cols)
      cols = 1;
    if ((max_arg_len + 1) * argc < term_width)
      cols = argc;
    rows = argc / cols;
    if (rows > term_height)
    	return ;
    if (argc % cols)
      ++rows;
    i = -1;

    args = g_select.args;
    first = args;
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
        while (str_len++ <= max_arg_len)
        	ft_putstr(" ");
        if (args->next == first)
        	break;
        args = args->next;
      }
      ft_putstr("\n");
    }
}