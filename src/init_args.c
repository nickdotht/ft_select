/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 23:19:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 02:57:51 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	free_args(void)
{
	t_args		*args;
	t_args		*first;
	t_args		*curr;

	args = g_select.args;
	first = args;
	while (args)
	{
		curr = args;
		free(args->value);
		free(curr);
		if (args->next == first)
			break;
		args = args->next;
	}
	args = NULL;
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
	t_args		*active;

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

void	insert_arg(char *value)
{
	t_args		*new;
	t_args		*last;

	new = (t_args *)ft_memalloc(sizeof(t_args));
	new->value = ft_strdup(value);
	new->type = get_arg_type(value);
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

void	init_args(char **av)
{
	int		i;

	i = -1;
	g_select.argc = 0;
	while (av[++i])
	{
		insert_arg(av[i]);
		g_select.argc++;
	}
	g_select.args_per_row = count_columns();
}