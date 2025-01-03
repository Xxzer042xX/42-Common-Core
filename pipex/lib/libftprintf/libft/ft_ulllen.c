/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulllen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:13:43 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/09/15 19:13:43 by mdelmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_ulllen(unsigned long long nb)
{
	unsigned long long	len;

	len = (nb <= 0);
	while (nb != 0)
	{
		nb /= 10;
		len += 1;
	}
	return (len);
}
