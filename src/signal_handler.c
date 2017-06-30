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
	tputs(tgetstr("cl", NULL), 1, ft_printnbr);
    column_display();
	g_select.args_per_row = count_columns();
}

void	suspend_signal_handler(void)
{
	char cp[2];

	cp[0] = g_select.attr.c_cc[VSUSP];
	cp[1] = 0;
	reset_default_conf();
	tputs(tgetstr("cl", NULL), 1, ft_printnbr);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, cp);
}

void	stop_signal_handler(void)
{
	reset_default_conf();
	tputs(tgetstr("cl", NULL), 1, ft_printnbr);
	free_args();
	exit(EXIT_SUCCESS);
}

void	signal_handler(int signo)
{
	char	*buf;

	buf = NULL;
	if (signo == SIGTSTP)
		suspend_signal_handler();
    else if (signo == SIGINT)
        stop_signal_handler();
    else if (signo == SIGCONT)
    {
    	init_custom_conf();
    	init_signal_handlers();
    	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
		tputs(tgetstr("vi", &buf), 1, ft_printnbr);
	    column_display();
    }
    else if (signo == SIGWINCH)
    	window_resize_handler();
}