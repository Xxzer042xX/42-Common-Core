/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:46:35 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/01 21:46:35 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p_s;

	p_s = (const unsigned char *)s;
	while (n--)
	{
		if (*p_s == (unsigned char)c)
			return ((void *)p_s);
		p_s++;
	}
	return (NULL);
}
