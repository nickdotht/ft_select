/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:47:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/02 03:19:55 by jrameau          ###   ########.fr       */
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
	t_arg	*tmp;
	t_arg	*first;

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

/*
** Returns the length of the longest value from the list of arguments
** 
** @param		N/A
** @return		The length of the longest value
*/

int		count_max_arg_len(void)
{
	int		max;
	int		curr_len;
	t_arg	*first;
	t_arg	*tmp;

	if (!g_select.args || !g_select.args->value)
		return (0);
	max = 0;
	tmp = g_select.args;
	first = tmp;
	while (tmp)
	{
		curr_len = ft_strlen(tmp->value);
		if (curr_len > max)
			max = curr_len;
		if (tmp->next == first)
			break ;
		tmp = tmp->next;
	}
	return (max);
}

/*
** Loads the entry for the passed in terminal name
** 
** Makes sure the file descriptor is a valid terminal type device.
** Then loads the entry from the terminfo database for name, if it exists.
** I'm using STDIN_FILENO instead of STDOUT_FILENO to take care of command substitutions.
** So we don't use the same file descriptor as the calling command.
** Using STDERR_FILENO would have worked too.
** i.e.: rm `./ft_ls test1 test2`
** 
** @param		tty_name 	entry name received from the environment variable
** @return		N/A
*/

void	load_entry(char *tty_name)
{
	int		res;
	char	buf[1024];

	if (!isatty(STDIN_FILENO))
    {
      	ft_putendl_fd("Not a terminal.", STDIN_FILENO);
    	tputs(tgetstr("te", NULL), 1, ft_printnbr);
     	exit(EXIT_FAILURE);
    }
	if ((res = tgetent(buf, tty_name)) < 1)
	{
		if (res == -1)
			ft_putendl_fd("Terminfo database not found. Exiting.", STDIN_FILENO);
		else if (res == 0)
			ft_putendl_fd("No such entry in the terminfo database. Exiting.", STDIN_FILENO);
    	tputs(tgetstr("te", NULL), 1, ft_printnbr);
		exit(EXIT_FAILURE);
	}
}

/*
** Resets the old attributes that we saved from 'init_custom_conf'
**
** It applies the old atributes to the terminal
** The ids "ve" amd "te" exit alternate screen mode and show the cursor respectively
**
** @param		N/A
** @return		N/A
*/

void	reset_default_conf(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_select.saved_attr);
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
	t_arg		*args;
	t_arg		*first;

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

/*
** Prints all selected arguments
**
** @param		void
** @return		N/A
*/

void	print_selected_args(void)
{
	t_arg		*args;
	t_arg		*first;

	args = g_select.args;
	first = args;
	while (args)
	{
		if (args->is_selected)
		{
			print_value_fd(args, STDOUT_FILENO);
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
** It first checks that we can access the terminal name from the environment
** Then loads the entry for the terminal name we just got
** Saves the old attributes to reset them later
** And applies our custom attributes to the terminal
** The ids "ti" and "vi" enter alternate screen mode (so we can later give back
** the shell the way it was) and hide the cursor respectively
**
** @param		N/A
** @return		N/A
*/

void	init_custom_conf(void)
{
	if (!(g_select.term_name = getenv("TERM")))
    {
        ft_putendl_fd("Could not find the terminal name.", STDIN_FILENO);
        reset_default_conf();
        exit(EXIT_SUCCESS);
    }
    load_entry(g_select.term_name);
	tcgetattr(STDIN_FILENO, &g_select.saved_attr);
	tcgetattr(STDIN_FILENO, &g_select.attr);
	g_select.attr.c_lflag &= ~(ICANON|ECHO);
	g_select.attr.c_cc[VMIN] = 1;
	g_select.attr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_select.attr);
	tputs(tgetstr("ti", NULL), 1, ft_printnbr);
	tputs(tgetstr("vi", NULL), 1, ft_printnbr);
}

/*
** Initializes the signal handlers
**
** @param		N/A
** @return		N/A
*/

void	init_signal_handlers(void)
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
		stop_signal_handler();
}

/*
** Validates the passed flag
**
** @param		arg		The passed flag without the first '-'
** @return		N/A
*/

void	validate_flag(char *arg)
{
	if ((arg[0] == 'r' && !arg[1]) || (arg[0] == '-' && ft_strequ(arg + 1, "real")))
		g_select.real_mode = 1;
	else
		print_usage();
}

void	folder_browsing(int key)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*name;
	char			*cwd;

	cwd = getwd(NULL);
	name = (key == O_KEY)
		? ft_pathjoin(cwd, (*g_select.active_arg)->value)
		: ft_strdup(ft_get_parent_path(cwd));
	if (!(dir = opendir(name)))
		return ;
	free_args();
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue ;
		insert_arg(entry->d_name);
	}
	closedir(dir);
	chdir(name);
}

/*
** Displays, in a loop, the columns of values and handles key presses
**
** Handles the following keys
** - Enter key: End the program
** - Space key: Select or unselect the active argument
** - Escape key: Stop the program
** - Backspace/Delete keys: Delete the active argument
** - Star key: Selects every argument
** - Minus key: Unselect every argument
** - O key: Opens and display the active argument if it's a valid folder
** - B key: Opens the parent of the current folder
** - Top/Right/Bottom/Left key: directions in the browser 
**
** @param		N/A
** @return		N/A
*/

void	on_key_press(void)
{
	long		c;

	while (1)
   	{
	    column_display();
	    c = 0;
	    read(STDIN_FILENO, &c, 8);
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
		else if (c == O_KEY || c == B_KEY)
			folder_browsing(c);
   		else
   			move(get_dir(c));
	}
}

/*
** Initializes ft_select
** 
** @param		ac		Arguments count
** @param		av		Arguments variable
** @return		0 on completion
*/

int		main(int ac, char **av)
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