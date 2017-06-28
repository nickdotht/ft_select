/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:47:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 16:43:52 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

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

int		args_max_len(void)
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

void	window_resize_handler(int sig)
{
	char	*buf;
	(void)sig;
	buf = NULL;
	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
    column_display(count_args(), args_max_len());
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
      ft_putendl("Not a terminal.");
      exit(EXIT_FAILURE);
    }
	res = tgetent(buf, tty_name);
	if (res < 1)
	{
		if (res == -1)
		{
			ft_putendl("Terminfo database not found. Exiting.");
		}
		else if (res == 0)
		{
			ft_putendl("No such entry in the terminfo database. Exiting.");
		}
		exit(EXIT_FAILURE);
	}
}

void	reset_input_mode (void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_select.saved_attr);
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

int		main(int ac, char **av)
{
    char    		*term_name;
    char			*buf;
    struct termios	attr;
    char			c[6];
    int				bytes_read;
    t_dir			dir;

    if (ac == 1)
        print_usage();
    if (!(term_name = getenv("TERM")))
    {
        ft_putendl("Could not find the terminal name.");
        return (0);
    }
    load_entry(term_name);
	tcgetattr (STDIN_FILENO, &g_select.saved_attr);
	tcgetattr (STDIN_FILENO, &attr);
	attr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &attr);
    init_args(av + 1);
    signal(SIGWINCH, window_resize_handler);
   	while (1)
   	{
	   	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
	    column_display(count_args(), args_max_len());
	    bytes_read = read(STDIN_FILENO, c, 5);
   		if (bytes_read == 1)
   		{
   			if (c[0] == '\012')
   				break;
   		}
   		else
   		{
   			dir = get_dir(c);
   			if (dir == UP_DIR)
   				move(UP_DIR);
   			else if (dir == RIGHT_DIR)
   				move(RIGHT_DIR);
   			else if (dir == DOWN_DIR)
   				move(DOWN_DIR);
   			else if (dir == LEFT_DIR)
   				move(LEFT_DIR);
   		}
	}
   	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
	ft_putendl("Print selected elements here!");
	reset_input_mode();
    return (0);
}