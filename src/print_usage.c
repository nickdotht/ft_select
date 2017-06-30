/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:52:07 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/29 00:58:53 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_usage(void) 
{
	ft_putendl_fd("Thank you for using ft_select. Here's how to use it:", STDERR_FILENO);
	ft_putendl_fd("./ft_select [-r | --real] argument1 [argument2 argument3 etc...]", STDERR_FILENO);
	exit(EXIT_FAILURE);
}