/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:57:26 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/01 20:57:26 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	if (n == 0 || dest == src)
		return (dest);
	p_src = (const unsigned char *)src;
	p_dest = (unsigned char *)dest;
	if (p_dest < p_src)
		ft_memcpy(p_dest, p_src, n);
	else
	{
		p_src += n;
		p_dest += n;
		while (n--)
			*(--p_dest) = *(--p_src);
	}
	return (dest);
}
