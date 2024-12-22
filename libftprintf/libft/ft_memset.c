/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:41:50 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/10/01 13:41:50 by mdelmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	byte;

	p_s = (unsigned char *)s;
	byte = (unsigned char)c;
	while (n--)
		*(p_s++) = byte;
	return (s);
}
