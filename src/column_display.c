/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:39:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 00:28:02 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/**
 * TODO: Remove the fact that the args are being printed from top to bottom
 * instead of left to right so this can become shorter. We need to do it anyway
 * because we need the properties of each argument to add colors and stuffs
 */

void    column_display(t_args *args, int argc, int max_arg_len)
{
    struct  winsize w;
    int     cols;
    int     rows;
    int     term_width;
    int     term_height;
    int     i;
    int		j;
    int     pos;
    char	**arr;
    t_args	*first;
    t_args	*tmp;

    if (!args)
    	return ;
    arr = (char **)ft_memalloc(sizeof(char *) * (argc + 1));
	i = 1;
	tmp = args;
	first = tmp;
	arr[0] = tmp->value;
	tmp = tmp->bottom;
	while (tmp && tmp != first)
	{
		arr[i++] = tmp->value;
		tmp = tmp->bottom;
	}
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
      pos = i;
      while (++j < cols)
      {
      	int str_len;
      	ft_putstr("\033[4;44m");
        ft_putstr(arr[pos]);
      	ft_putstr("\033[0m");
        str_len = ft_strlen(arr[pos]);
        while (str_len++ <= max_arg_len)
        	ft_putstr(" ");
        pos += rows;
        if (pos >= argc)
          break;
      }
      ft_putstr("\n");
    }
}