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
	return (write(STDIN_FILENO, &nbr, 1));
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

	if (!g_select.args)
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

	if (!isatty(STDIN_FILENO))
    {
      ft_putendl_fd("Not a terminal.", STDIN_FILENO);
      exit(EXIT_FAILURE);
    }
	res = tgetent(buf, tty_name);
	if (res < 1)
	{
		if (res == -1)
		{
			ft_putendl_fd("Terminfo database not found. Exiting.", STDIN_FILENO);
		}
		else if (res == 0)
		{
			ft_putendl_fd("No such entry in the terminfo database. Exiting.", STDIN_FILENO);
		}
		exit(EXIT_FAILURE);
	}
}

void	reset_default_conf(void)
{
	char	*buf;

	buf = NULL;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_select.saved_attr);
	tputs(tgetstr("ve", &buf), 1, ft_printnbr);
}

t_dir	get_dir(char *c)
{
	if (c[0] != 27 && c[1] != 91)
		return (DEFAULT_DIR);
	if (c[2] == 65)
		return (UP_DIR);
	else if (c[2] == 66)
		return (DOWN_DIR);
	else if (c[2] == 67)
		return (RIGHT_DIR);
	else if (c[2] == 68)
		return (LEFT_DIR);
	return (DEFAULT_DIR);
}

void	toggle_selection(void)
{
	(*g_select.active_arg)->is_selected = !(*g_select.active_arg)->is_selected;
	g_select.active_arg = &(*g_select.active_arg)->next;
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
			ft_putstr(args->value);
			ft_putchar(' ');
		}
		if (args->next == first)
			break;
		args = args->next;
	}
}

void	init_custom_conf()
{
    struct termios	attr;

	if (!(g_select.term_name = getenv("TERM")))
    {
        ft_putendl_fd("Could not find the terminal name.", STDIN_FILENO);
        free_args();
        return ;
    }
    load_entry(g_select.term_name);
	tcgetattr(STDIN_FILENO, &g_select.saved_attr);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~(ICANON|ECHO);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
}

void	init_signal_handlers()
{
	signal(SIGWINCH, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGCONT, signal_handler);
}

void	delete_active_arg(void)
{
	remove_arg();
	if (!g_select.args)
	{
		stop_signal_handler();
	}
}

int		main(int ac, char **av)
{
    char			*buf;
    char			c[6];
    int				bytes_read;

    if (ac == 1)
        print_usage();
    init_custom_conf();
    init_args(av + 1);
    init_signal_handlers();
	buf = NULL;
	tputs(tgetstr("vi", &buf), 1, ft_printnbr);
   	while (1)
   	{
	   	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
	    column_display();
	    bytes_read = read(STDIN_FILENO, c, 5);
   		if (bytes_read == 1)
   		{
   			if (c[0] == 10)
   				break;
   			else if (c[0] == 32)
   				toggle_selection();
   			else if (c[0] == 27)
   				stop_signal_handler();
   			else if (c[0] == 127 || c[0] == 14)
   				delete_active_arg();
   		}
   		else
   			move(get_dir(c));
	}
   	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
	print_selected_args();
	reset_default_conf();
    return (0);
}