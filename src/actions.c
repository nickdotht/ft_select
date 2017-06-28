/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:43:41 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 11:28:57 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	move_down()
{
	t_args		*tmp;

	tmp = g_args;
	while (tmp)
	{
		if (tmp->is_active && tmp->bottom)
		{
			tmp->is_active = 0;
			tmp->bottom->is_active = 1;
		}
		tmp = tmp->right;
	}
}

void	move_up()
{
	t_args		*tmp;

	tmp = g_args;
	while (tmp)
	{
		if (tmp->is_active && tmp->top)
		{
			tmp->is_active = 0;
			tmp->top->is_active = 1;
		}
		tmp = tmp->right;
	}
}

void	move_right()
{
	t_args		*tmp;

	tmp = g_args;
	while (tmp)
	{
		if (tmp->is_active && tmp->right)
		{
			tmp->is_active = 0;
			tmp->right->is_active = 1;
		}
		tmp = tmp->right;
	}
}

void	move_left()
{
	t_args		*tmp;

	tmp = g_args;
	while (tmp)
	{
		if (tmp->is_active && tmp->left)
		{
			tmp->is_active = 0;
			tmp->left->is_active = 1;
		}
		tmp = tmp->right;
	}
}