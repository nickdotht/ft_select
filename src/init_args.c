/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 23:19:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/28 00:02:11 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

// BONUS
// t_type	get_arg_type(char *entry_name)
// {

// }

void	init_args(t_args **args, char **av)
{
	int		i;
	t_args	**head;
	t_args	*prev;
	t_args	*first;

	prev = NULL;
	head = args;
	i = -1;
	first = NULL;
	while (av[++i])
	{
		*args = (t_args *)ft_memalloc(sizeof(t_args) * 1);
		(*args)->value = ft_strdup(av[i]);
		(*args)->top = (prev) ? prev : NULL;
		(*args)->right = NULL;
		(*args)->bottom = (!av[i]) ? first : NULL;
		(*args)->left = NULL;
		// (*args)->type = get_arg_type(av[i]); //BONUS
		(*args)->is_active = (i == 0) ? 1 : 0;
		(*args)->is_selected = 0;
		if (prev)
			prev->bottom = *args;
		else
			first = *args;
		prev = *args;
		args = &(*args)->bottom;
	}
	args = head;
}