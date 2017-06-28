/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 21:45:09 by jrameau           #+#    #+#             */
/*   Updated: 2017/06/27 21:53:15 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * Basically another putchar
 * @param  nbr the digit to print
 * @return     The number of written bytes, -1 on failure
 */

int		ft_printnbr(int nbr)
{
	return (write(1, &nbr, 1));
}