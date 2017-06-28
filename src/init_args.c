/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 23:19:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 11:37:22 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

// BONUS
// t_type	get_arg_type(char *entry_name)
// {

// }

void	init_args(char **av)
{
	int		i;
	t_args	**tmp;
	t_args	*prev;
	t_args	*first;

	prev = NULL;
	tmp = &g_args;
	i = -1;
	first = NULL;
	while (av[++i])
	{
		*tmp = (t_args *)ft_memalloc(sizeof(t_args));
		(*tmp)->value = ft_strdup(av[i]);
		(*tmp)->top = NULL;
		(*tmp)->left = (prev) ? prev : NULL;
		(*tmp)->is_active = (i == 0) ? 1 : 0;
		(*tmp)->is_selected = 0;
		if (prev)
			prev->right = *tmp;
		else
			first = *tmp;
		if (!av[i + 1])
		{
			// (*tmp)->right = first;
			first->left = *tmp;
		}
		prev = *tmp;
		tmp = &(*tmp)->right;
	}
}