/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 03:48:22 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/10 03:48:22 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		l_total;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	l_total = (ft_strlen(s1) + ft_strlen(s2) + 1);
	join = (char *)malloc(sizeof(char) * l_total);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, (ft_strlen(s1) + 1));
	ft_strlcat(join, s2, l_total);
	return (join);
}
