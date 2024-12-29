/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:28:50 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/05 18:28:50 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_pad_int(int padding, char c)
{
	int		char_count;

	char_count = 0;
	if (padding < 0)
		return (0);
	while (padding-- > 0)
	{
		if (write(1, &c, 1) == -1)
			return (-1);
		char_count++;
	}
	return (char_count);
}
