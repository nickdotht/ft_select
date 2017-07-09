/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:47:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/04 08:02:38 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/*
** Loads the entry for the passed in terminal name
**
** Makes sure the file descriptor is a valid terminal type device,
** then loads the entry from the terminfo database for name, if it exists.
** I'm using STDERR_FILENO instead of STDOUT_FILENO to take care of command
** substitutions so that we don't use the same file descriptor as the calling
** command. Using STDIN_FILENO would have been a problem too for some commands
** i.e.: rm `./ft_ls test1 test2`
**
** @param		tty_name 	entry name received from the environment variable
** @return		N/A
*/

static void	load_entry(char *tty_name)
{
	int		res;
	char	buf[1024];

	if (!isatty(STDERR_FILENO))
	{
		ft_putendl_fd("Not a terminal.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if ((res = tgetent(buf, tty_name)) < 1)
	{
		if (res == -1)
			ft_putendl_fd("Terminfo database not found. Exiting.",
				STDERR_FILENO);
		else if (res == 0)
			ft_putendl_fd("No such entry in the terminfo database. Exiting.",
				STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

/*
** Prints all selected arguments
**
** @param		void
** @return		N/A
*/

static void	print_selected_args(void)
{
	t_arg		*args;
	t_arg		*first;
	int			count;

	args = g_select.args;
	first = args;
	count = 1;
	while (args)
	{
		if (args->is_selected)
		{
			print_value_fd(args, STDOUT_FILENO);
			count++;
			if (count < g_select.selected_count)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		if (args->next == first)
			break ;
		args = args->next;
	}
}

/*
** Initializes the custom terminal configurations
**
** It first checks that we can access the terminal name from the environment,
** then loads the entry for the terminal name we just got,
** saves the old attributes to reset them later
** and applies our custom attributes to the terminal.
** The ids "ti" and "vi" enter alternate screen mode (so we can later give back
** the shell the way it was) and hide the cursor respectively
**
** @param		N/A
** @return		N/A
*/

void		init_custom_conf(void)
{
	if (!(g_select.term_name = getenv("TERM")))
	{
		ft_putendl_fd("Could not find the terminal name.", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	load_entry(g_select.term_name);
	tcgetattr(STDERR_FILENO, &g_select.old_attr);
	tcgetattr(STDERR_FILENO, &g_select.attr);
	g_select.attr.c_lflag &= ~(ICANON | ECHO);
	g_select.attr.c_cc[VMIN] = 1;
	g_select.attr.c_cc[VTIME] = 0;
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.attr);
	tputs(tgetstr("ti", NULL), 1, ft_printnbr);
	tputs(tgetstr("vi", NULL), 1, ft_printnbr);
}

/*
** Initializes the signal handlers
**
** @param		N/A
** @return		N/A
*/

void		init_signal_handlers(void)
{
	signal(SIGWINCH, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
}

/*
** Initializes ft_select
**
** @param		ac		Arguments count
** @param		av		Arguments variable
** @return		0 on completion
*/

int			main(int ac, char **av)
{
	if (ac < 2 || (ac == 2 && av[1][0] == '-'))
		print_usage();
	if (av[1][0] == '-' && av[1][1])
		validate_flag(av[1] + 1);
	init_custom_conf();
	init_args((av[1][0] == '-') ? av + 2 : av + 1);
	init_signal_handlers();
	on_key_press();
	reset_default_conf();
	print_selected_args();
	free_args();
	return (0);
}
