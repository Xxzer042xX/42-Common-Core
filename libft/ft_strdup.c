/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:04 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/09/15 18:29:04 by mdelmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*p_dup;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!(dup))
		return (NULL);
	p_dup = dup;
	while (*s)
		*p_dup++ = *s++;
	*p_dup = *s;
	return (dup);
}
