/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 03:56:13 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/10 03:56:13 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = (ft_strlen(s1) - 1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	trim = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, &s1[start], (end - start) + 2);
	return (trim);
}
