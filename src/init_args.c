/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 23:19:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/02 00:05:30 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	free_args(void)
{
	t_arg		*first;
	t_arg		*curr;

	first = g_select.args;
	while (g_select.args)
	{
		curr = g_select.args;
		g_select.argc--;
		if (g_select.args->next == first)
			break;
		free(g_select.args->value);
		g_select.args = g_select.args->next;
		free(curr);
	}
	g_select.args_per_row = 0;
	g_select.args = NULL;
}

void	delete_file(char *fname)
{
	struct stat f;

	if (lstat(fname, &f) == -1)
		return ;
	remove(fname);
}

void	remove_arg()
{
	t_arg		*active;

	if (!g_select.active_arg)
		return ;
	active = *g_select.active_arg;
	if (g_select.args == active)
		g_select.args = (active->next == active) ? NULL : active->next;
	else
		g_select.active_arg = &active->next;
	active->next->prev = active->prev;
	active->prev->next = active->next;
	if (g_select.real_mode)
		delete_file(active->value);
	g_select.argc--;
	free(active->value);
	free(active);
	if (!g_select.argc)
		stop_signal_handler();
	g_select.args_per_row = count_columns();
}

t_type	get_arg_type(char *path)
{
	char				*name;

	name = ft_strrchr(path, '/') ? ft_strrchr(path, '/') + 1 : path;
	if (ft_strendswith(name, ".c"))
		return (C_T);
	if (ft_strendswith(name, ".o"))
		return (O_T);
	if (ft_strendswith(name, ".h"))
		return (H_T);
	if (ft_strendswith(name, ".a"))
		return (A_T);
	if (ft_strequ(name, "Makefile"))
		return (MAKEFILE_T);
	if (name[0] == '.')
		return DOT_T;
	return (UNKNOWN_T);
}

/*
** Appends a value as an argument into the list of arguments or creates it
** if it doesn't exist
**
** @param		value		The value to insert
** @return		N/A
*/

void	insert_arg(char *value)
{
	t_arg		*new;
	t_arg		*last;

	new = (t_arg *)ft_memalloc(sizeof(t_arg));
	new->value = ft_strdup(value);
	new->type = get_arg_type(value);
	g_select.argc++;
	if (!g_select.args)
	{
		new->prev = new;
		new->next = new;
		g_select.args = new;
		g_select.active_arg = &g_select.args;
		return ;
	}
	last = g_select.args->prev;
	new->next = g_select.args;
	g_select.args->prev = new;
	new->prev = last;
	last->next = new;
}

/*
** Initializes the list of argument values so we can display them later
**
** I'm using a global variable so I can be able to free the memory once
** the program gets killed, there are no other methods of doing this. Unless we
** don't use signals anymore, but for this project, I wasn't allowed to use anything else
**
** @param		av		Arguments variable
** @return		N/A
*/

void	init_args(char **av)
{
	int		i;

	i = -1;
	g_select.argc = 0;
	while (av[++i])
		insert_arg(av[i]);
	g_select.args_per_row = count_columns();
}