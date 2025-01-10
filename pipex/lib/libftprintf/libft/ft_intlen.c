/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 02:22:08 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/24 02:22:08 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int	len;

	len = (n <= 0);
	while (n != 0)
	{
		n /= 10;
		len += 1;
	}
	return (len);
}

/*
int	ft_int_len(int n)
{
	int	sign;

	sign = (n < 0);
	if (n < 0)
		n *= -1;
	if (n == 0)
		return (1);
	return (sign + 1 + ft_int_len(n / 10));
}
*/