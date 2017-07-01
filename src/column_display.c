/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:39:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 00:47:35 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int		get_term_size(int w_or_h)
{
    struct  winsize w;

    ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
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

void  print_arg_value(t_args *arg)
{
  if (arg->type == C_T)
    ft_putstr_fd(C_COLOR, STDERR_FILENO);
  else if (arg->type == O_T)
    ft_putstr_fd(O_COLOR, STDERR_FILENO);
  else if (arg->type == H_T)
    ft_putstr_fd(H_COLOR, STDERR_FILENO);
  else if (arg->type == MAKEFILE_T)
    ft_putstr_fd(MAKEFILE_COLOR, STDERR_FILENO);
  else if (arg->type == DOT_T)
    ft_putstr_fd(DOT_COLOR, STDERR_FILENO);
  else if (arg->type == A_T)
    ft_putstr_fd(A_COLOR, STDERR_FILENO);
  ft_putstr_fd(arg->value, STDERR_FILENO);
}

void  display_args(t_args *args, t_args *first, int rows, int cols)
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
          ft_putstr_fd(UNDERLINED, STDERR_FILENO);
        if (args->is_selected)
          ft_putstr_fd(REVERSE_VIDEO_COLOR, STDERR_FILENO);
        print_arg_value(args);
        ft_putstr_fd(DEFAULT_COLOR, STDERR_FILENO);
        str_len = ft_strlen(args->value);
        while (str_len++ <= count_max_arg_len())
          ft_putstr_fd(" ", STDERR_FILENO);
        if (args->next == first)
          break;
        args = args->next;
      }
      ft_putstr_fd("\n", STDERR_FILENO);
    }
}

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