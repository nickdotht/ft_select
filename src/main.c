/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:47:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 00:18:58 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int		count_args(t_args *args)
{
	int		count;
	t_args	*tmp;
	t_args	*first;

	if (!args)
		return (0);
	count = 1;
	tmp = args;
	first = tmp;
	tmp = tmp->bottom;
	while (tmp && tmp != first)
	{
		count++;
		tmp = tmp->bottom;
	}
	return (count);
}

int		args_max_len(t_args *args)
{
	int		max;
	int		curr_len;
	t_args	*first;
	t_args	*tmp;

	if (!args)
		return (0);
	tmp = args;
	max = ft_strlen(tmp->value);
	first = tmp;
	tmp = tmp->bottom;
	while (tmp && tmp != first)
	{
		curr_len = ft_strlen(tmp->value);
		if (curr_len > max)
			max = curr_len;
		tmp = tmp->bottom;
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
		exit(0);
	}
}

int		main(int ac, char **av)
{
    char    *term_name;
    char	*buf;
    t_args	*args;

    if (ac == 1)
        print_usage();
    if (!(term_name = getenv("TERM")))
    {
        ft_putendl("Could not find the terminal name.");
        return (0);
    }
    load_entry(term_name);
    buf = NULL;
    init_args(&args, av + 1);
    while (1)
    {
    	tputs(tgetstr("cl", &buf), 1, ft_printnbr);
	    column_display(args, count_args(args), args_max_len(args));
	    sleep(1);
    }
    return (0);
}