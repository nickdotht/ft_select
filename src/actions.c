/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:43:41 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 16:13:18 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

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
}