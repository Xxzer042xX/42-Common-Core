/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:11:43 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/09/15 19:11:43 by mdelmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		sign;

	sign = (n < 0);
	size = ft_intlen(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!(result))
		return (NULL);
	result[size] = '\0';
	if (sign)
	{
		result[0] = '-';
		n *= -1;
	}
	if (n == 0)
		result[0] = '0';
	while (size > sign)
	{
		result[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
