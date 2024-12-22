/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:53:52 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/09/15 15:53:52 by mdelmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l_src;
	size_t	l_dest;

	l_src = ft_strlen(src);
	l_dest = ft_strlen(dest);
	if (size <= l_dest)
		return (size + l_src);
	ft_strlcpy(dest + l_dest, src, size - l_dest);
	return (l_src + l_dest);
}
