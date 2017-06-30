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
    column_display();
	g_select.args_per_row = count_columns();
}

void	suspend_signal_handler(void)
{
	reset_default_conf();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\032");
}

void	stop_signal_handler(void)
{
	reset_default_conf();
	free_args();
	exit(EXIT_SUCCESS);
}

void	signal_handler(int signo)
{
	char	*buf;

	buf = NULL;
	if (signo == SIGTSTP)
		suspend_signal_handler();
    else if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP
    	|| signo == SIGKILL)
        stop_signal_handler();
    else if (signo == SIGCONT)
    {
    	init_custom_conf();
    	init_signal_handlers();
	    column_display();
    }
    else if (signo == SIGWINCH)
    	window_resize_handler();
}