/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 23:19:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 01:53:28 by jrameau          ###   ########.fr       */
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
	curr = args;
	free(args->value);
	args = args->next;
	free(curr);
	while (args != first)
	{
		curr = args;
		free(args->value);
		args = args->next;
		free(curr);
	}
	args = NULL;
}

void	remove_arg(t_args **active)
{
	if (!*active)
		return ;
	if (g_select.args == (*active))
	{
		g_select.args = (*active)->next;
	}
	if ((*active)->next)
		g_select.args->prev = (*active)->prev;
	if ((*active)->prev)
		g_select.args->next = (*active)->next;
	free(*active);
	active = NULL;
}

void	insert_arg(char *value)
{
	t_args		*new;
	t_args		*last;

	new = (t_args *)ft_memalloc(sizeof(t_args));
	new->value = ft_strdup(value);
	if (g_select.args == NULL)
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