/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:43:41 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/02 18:18:38 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/*
** Moves up the argument list
**
** @param		N/A
** @return		N/A
*/

static void	move_up(void)
{
	int		i;
	t_arg	*tmp;
	int		cols;

	i = 0;
	tmp = *g_select.active_arg;
	cols = count_columns();
	while (++i < cols)
		tmp = tmp->prev;
	g_select.active_arg = &tmp->prev;
}

/*
** Moves down the argument list
**
** @param		N/A
** @return		N/A
*/

static void	move_down(void)
{
	int		i;
	t_arg	*tmp;
	int		cols;

	i = 0;
	tmp = *g_select.active_arg;
	cols = count_columns();
	while (++i < cols)
		tmp = tmp->next;
	g_select.active_arg = &tmp->next;
}

/*
** Provides argument browsing capabilities using the arrow keys
**
** @param		direction		the direction in which to go
** @return		N/A
*/

void		move(t_dir direction)
{
	t_arg		*active;

	active = *g_select.active_arg;
	if (direction == RIGHT_DIR)
		g_select.active_arg = &active->next;
	else if (direction == LEFT_DIR)
		g_select.active_arg = &active->prev;
	else if (direction == UP_DIR)
		move_up();
	else if (direction == DOWN_DIR)
		move_down();
}
