/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:47:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 02:51:46 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int		ft_printnbr(int nbr)
{
	return (write(STDERR_FILENO, &nbr, 1));
}

int		count_args(void)
{
	int		count;
	t_args	*tmp;
	t_args	*first;

	if (!g_select.args)
		return (0);
	count = 1;
	tmp = g_select.args;
	first = tmp;
	tmp = tmp->next;
	while (tmp && tmp != first)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int		count_max_arg_len(void)
{
	int		max;
	int		curr_len;
	t_args	*first;
	t_args	*tmp;

	if (!g_select.args || !g_select.args->value)
		return (0);
	tmp = g_select.args;
	max = ft_strlen(tmp->value);
	first = tmp;
	tmp = tmp->next;
	while (tmp && tmp != first)
	{
		curr_len = ft_strlen(tmp->value);
		if (curr_len > max)
			max = curr_len;
		tmp = tmp->next;
	}
	return (max);
}

/**
 * Loads the entry for tty_name
 * @param tty_name entry name received from the environment variable
 */

void	load_entry(char *tty_name)
{
	int		res;
	char	buf[1024];

	if (!isatty(STDERR_FILENO))
    {
      ft_putendl_fd("Not a terminal.", STDERR_FILENO);
    tputs(tgetstr("te", NULL), 1, ft_printnbr);
      exit(EXIT_FAILURE);
    }
	res = tgetent(buf, tty_name);
	if (res < 1)
	{
		if (res == -1)
		{
			ft_putendl_fd("Terminfo database not found. Exiting.", STDERR_FILENO);
		}
		else if (res == 0)
		{
			ft_putendl_fd("No such entry in the terminfo database. Exiting.", STDERR_FILENO);
		}
		exit(EXIT_FAILURE);
	}
}

void	reset_default_conf(void)
{
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.saved_attr);
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
}

t_dir	get_dir(long c)
{
	if (c == UP_KEY)
		return (UP_DIR);
	else if (c == DOWN_KEY)
		return (DOWN_DIR);
	else if (c == RIGHT_KEY)
		return (RIGHT_DIR);
	else if (c == LEFT_KEY)
		return (LEFT_DIR);
	return (DEFAULT_DIR);
}

void	toggle_selection(void)
{
	(*g_select.active_arg)->is_selected = !(*g_select.active_arg)->is_selected;
	if ((*g_select.active_arg)->is_selected)
		g_select.active_arg = &(*g_select.active_arg)->next;
}

void	toggle_all_args(long key)
{
	t_args		*args;
	t_args		*first;

	args = g_select.args;
	first = args;
	while (args)
	{
		args->is_selected = (key == STAR_KEY) ? 1 : 0;
		if (args->next == first)
			break;
		args = args->next;
	}
}

void	print_selected_args(void)
{
	t_args		*args;
	t_args		*first;

	args = g_select.args;
	first = args;
	while (args)
	{
		if (args->is_selected)
		{
			ft_putstr_fd(args->value, STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		if (args->next == first)
			break;
		args = args->next;
	}
}

void	init_custom_conf()
{
	if (!(g_select.term_name = getenv("TERM")))
    {
        ft_putendl_fd("Could not find the terminal name.", STDERR_FILENO);
        reset_default_conf();
        exit(EXIT_SUCCESS);
    }
    load_entry(g_select.term_name);
	tcgetattr(STDERR_FILENO, &g_select.saved_attr);
	tcgetattr(STDERR_FILENO, &g_select.attr);
	g_select.attr.c_lflag &= ~(ICANON|ECHO);
	g_select.attr.c_cc[VMIN] = 1;
	g_select.attr.c_cc[VTIME] = 0;
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.attr);
	tputs(tgetstr("ti", NULL), 1, ft_printnbr);
	tputs(tgetstr("vi", NULL), 1, ft_printnbr);
}

void	init_signal_handlers()
{
	signal(SIGWINCH, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGCONT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGKILL, signal_handler);
}

void	delete_active_arg(void)
{
	remove_arg();
	if (!g_select.args)
	{
		stop_signal_handler();
	}
}

void	validate_flag(char *arg)
{
	if ((arg[0] == 'r' && !arg[1]) || (arg[0] == '-' && ft_strequ(arg + 1, "real")))
		g_select.real_mode = 1;
	else
		print_usage();
}

int		main(int ac, char **av)
{
    long			c;

    if (ac == 1)
        print_usage();
    if (av[1][0] == '-' && av[1][1])
    	validate_flag(av[1] + 1);
    init_custom_conf();
    init_args((av[1][0] == '-') ? av + 2 : av + 1);
    init_signal_handlers();
   	while (1)
   	{
	    column_display();
	    c = 0;
	    read(STDERR_FILENO, &c, 8); // try to read 1 char at a time to check if it still works
		if (c == ENTER_KEY)
			break;
		else if (c == SPC_KEY)
			toggle_selection();
		else if (c == ESC_KEY)
			stop_signal_handler();
		else if (c == BSP_KEY || c == DEL_KEY)
			delete_active_arg();
		else if (c == STAR_KEY || c == MINUS_KEY)
			toggle_all_args(c);
   		else
   			move(get_dir(c));
	}
	reset_default_conf();
	print_selected_args();
	free_args();
    return (0);
}