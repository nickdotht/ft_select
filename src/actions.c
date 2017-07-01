/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:43:41 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 21:21:27 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	move_up(t_args *active)
{
	int		i;
	t_args	*tmp;
	int		cols;

	i = 0;
	tmp = active;
	cols = count_columns();
	while (++i < cols)
		tmp = tmp->prev;
	if (i == cols)
		g_select.active_arg = &tmp->prev;
}

void	move_down(t_args *active)
{
	int		i;
	t_args	*tmp;
	int		cols;

	i = 0;
	tmp = active;
	cols = count_columns();
	while (++i < cols)
		tmp = tmp->next;
	if (i == cols)
		g_select.active_arg = &tmp->next;
}

void	move(t_dir direction)
{
	t_args		*active;

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
		move_up(active);	
	}
	else if (direction == DOWN_DIR)
	{
		move_down(active);
	}
}