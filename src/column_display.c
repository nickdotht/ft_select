/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:39:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 11:11:38 by jrameau          ###   ########.fr       */
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
  	int		pos;

    if (!g_args)
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
    pos = 0;
    i = -1;
    while (++i < rows)
    {
      j = -1;
      while (++j < cols)
      {
      	if (g_args[pos].is_active)
      		ft_putstr("\033[4;m");
        ft_putstr(g_args[pos].value);
      	ft_putstr("\033[0m");
        str_len = ft_strlen(g_args[pos].value);
        while (str_len++ <= max_arg_len)
        	ft_putstr(" ");
        pos++;
        if (pos >= argc)
          break;
      }
      ft_putstr("\n");
    }
}