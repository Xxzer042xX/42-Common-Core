/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_padding_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:45:31 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/26 21:50:22 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

/*
 Writes spaces for specified padding.
 Prints 'padding' number of spaces to standard output.
*/
int	ft_print_str_padding(int padding)
{
	int	char_count;

	char_count = 0;
	if (padding < 0)
		return (0);
	while (padding-- > 0)
	{
		if (write(1, " ", 1) == -1)
			return (-1);
		char_count++;
	}
	return (char_count);
}
