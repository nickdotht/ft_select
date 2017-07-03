/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 22:38:53 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/03 02:47:23 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/*
** Handles the suspend signal (ctrl + z)
**
** It resets the default terminal configurations,
** sets the suspend signal back to the default behavior
** and yields the suspend signal (/032 or /x1A) to keep suspending the program.
**
** @param		N/A
** @return		N/A
*/

static void	suspend_signal_handler(void)
{
	reset_default_conf();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

/*
** Handles most of the stop signals (ctrl + c, kill, etc...)
**
** It resets the default terminal configurations,
** frees all allocated memories from the global variable
** and exits
**
** @param		N/A
** @return		N/A
*/

void		stop_signal_handler(void)
{
	reset_default_conf();
	free_args();
	exit(EXIT_SUCCESS);
}

/*
** Handles all the signals initilized during 'init_signal_handlers'
**
** @param		signo		The signal number of the current signal
** @return		N/A
*/

void		signal_handler(int signo)
{
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
		column_display();
}
