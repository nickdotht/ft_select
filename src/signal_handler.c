/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 22:38:53 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 01:02:37 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	window_resize_handler(void)
{
	char	*buf;

	buf = NULL;
	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
    column_display();
	g_select.args_per_row = count_columns();
}

void	abort_signal_handler(void)
{
	reset_default_conf();
	exit(EXIT_SUCCESS);
}

void	stop_signal_handler(void)
{
	reset_default_conf();
	free_args();
	exit(EXIT_SUCCESS);
}

void		signal_handler(int signo)
{
	if (signo == SIGABRT)
		abort_signal_handler();
    else if (signo == SIGINT || signo == SIGSTOP || signo == SIGKILL)
        stop_signal_handler();
    else if (signo == SIGCONT)
    {
    	init_custom_conf();
    	init_signal_handlers();
    }
    else if (signo == SIGWINCH)
    	window_resize_handler();
}