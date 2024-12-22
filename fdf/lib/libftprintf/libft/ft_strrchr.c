/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:57:04 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/09 14:57:04 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurence;

	last_occurence = NULL;
	while (*s)
	{
		if (*s == (const char)c)
			last_occurence = s;
		s++;
	}
	if ((const char)c == '\0')
		return ((char *)s);
	return ((char *)last_occurence);
}
