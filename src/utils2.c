/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 17:48:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/07/03 01:31:31 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

/*
** Resets the old attributes that we saved from 'init_custom_conf'
**
** It applies the old atributes to the terminal
** The ids "ve" amd "te" exit alternate screen mode and show the cursor
** respectively.
**
** @param		N/A
** @return		N/A
*/

void	reset_default_conf(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_select.old_attr);
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
}

/*
** Selects or unselects all arguments from the list depending on 'key'
**
** @param		key		The pressed key (STAR_KEY or MINUS_KEY)
** @return		N/A
*/

void	toggle_all_args(long key)
{
	t_arg		*args;
	t_arg		*first;

	args = g_select.args;
	first = args;
	while (args)
	{
		args->is_selected = (key == STAR_KEY) ? 1 : 0;
		if (args->next == first)
			break ;
		args = args->next;
	}
}

/*
** Yet another implementation of putchar
**
** My libft's ft_putchar doesn't use the same data types, and I would rather
** not modify it for compatibility issues.
**
** @param		nbr		The char/number to print
** @return		The amount of bytes written
*/

int		ft_printnbr(int nbr)
{
	return (write(STDIN_FILENO, &nbr, 1));
}

/*
** Returns the length of the longest value from the list of arguments
**
** @param		N/A
** @return		The length of the longest value
*/

int		count_max_arg_len(void)
{
	int		max;
	int		curr_len;
	t_arg	*first;
	t_arg	*tmp;

	if (!g_select.args || !g_select.args->value)
		return (0);
	max = 0;
	tmp = g_select.args;
	first = tmp;
	while (tmp)
	{
		curr_len = ft_strlen(tmp->value);
		if (curr_len > max)
			max = curr_len;
		if (tmp->next == first)
			break ;
		tmp = tmp->next;
	}
	return (max);
}
