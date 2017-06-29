/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:43:41 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 20:52:44 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	move(t_dir direction)
{
	t_args		*active;
	t_args		*tmp;
	int			i;

	active = *g_select.active_arg;
	if (direction == RIGHT_DIR)
	{
		g_select.active_arg = &active->next;
	}
	else if (direction == LEFT_DIR)
	{
		g_select.active_arg = &active->prev;
	}
	else if (direction == UP_DIR)
	{
		i = 0;
		tmp = active;
		while (++i < g_select.args_per_row && tmp->prev)
			tmp = tmp->prev;
		if (i == g_select.args_per_row)
			g_select.active_arg = &tmp->prev;
	}
	else if (direction == DOWN_DIR)
	{
		i = 0;
		tmp = active;
		while (++i < g_select.args_per_row && tmp->next)
			tmp = tmp->next;
		if (i == g_select.args_per_row)
			g_select.active_arg = &tmp->next;
	}
}