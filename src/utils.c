/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 17:41:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/04 07:17:06 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/*
** Returns the appropriate direction depending on the value of 'c'
**
** @param		c		The pressed key, represented as a long integer
**						for easier detection
** @return		The direction that matches the pressed key
*/

static t_dir	get_dir(long c)
{
	if (c == UP_KEY)
		return (UP_DIR);
	else if (c == DOWN_KEY)
		return (DOWN_DIR);
	else if (c == RIGHT_KEY)
		return (RIGHT_DIR);
	else if (c == LEFT_KEY)
		return (LEFT_DIR);
	else
		return (DEFAULT_DIR);
}

/*
** Toggles the selection state of the active argument
**
** On selection, sets the next argument as active
**
** @param		N/A
** @return		N/A
*/

static void		toggle_selection(void)
{
	(*g_select.active_arg)->is_selected = !(*g_select.active_arg)->is_selected;
	g_select.selected_count += ((*g_select.active_arg)->is_selected) ? 1 : -1;
	if ((*g_select.active_arg)->is_selected)
		g_select.active_arg = &(*g_select.active_arg)->next;
}

/*
** Validates the passed in flag 'arg'
**
** @param		arg		The passed flag without the first '-'
** @return		N/A
*/

void			validate_flag(char *arg)
{
	if ((arg[0] == 'r' && !arg[1]) || (arg[0] == '-' &&
			ft_strequ(arg + 1, "real")))
		g_select.real_mode = 1;
	else
		print_usage();
}

/*
** Provides folder browsing capabilities
**
** Press 'O' on a folder to open and show its files and press 'B' to go
** back to the parent root.
**
** @param		key		The pressed key (O_KEY or B_KEY)
** @return		N/A
*/

static void		folder_browsing(int key)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*name;
	char			*cwd;

	cwd = getcwd(NULL, MAXPATHLEN);
	name = (key == O_KEY)
		? ft_pathjoin(cwd, (*g_select.active_arg)->value)
		: ft_get_parent_path(cwd);
	free(cwd);
	if (!(dir = opendir(name)))
		return (free(name));
	free_args();
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue ;
		insert_arg(entry->d_name);
	}
	closedir(dir);
	chdir(name);
	free(name);
	name = NULL;
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
** - Top/Right/Bottom/Left key: navigation directions in the browser
**
** @param		N/A
** @return		N/A
*/

void			on_key_press(void)
{
	long		c;

	while (1)
	{
		column_display();
		c = 0;
		read(STDERR_FILENO, &c, 8);
		if (c == ENTER_KEY)
			break ;
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
