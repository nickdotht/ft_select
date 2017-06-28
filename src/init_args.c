/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 23:19:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 16:38:52 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

// BONUS
// t_type	get_arg_type(char *entry_name)
// {

// }

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
	while (av[++i])
		insert_arg(av[i]);
}