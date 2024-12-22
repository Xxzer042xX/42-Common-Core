/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:07:12 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/13 12:07:12 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*p_join;

	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join || !s1 || !s2)
		return (NULL);
	p_join = join;
	while (*s1)
		*p_join++ = *s1++;
	while (*s2)
		*p_join++ = *s2++;
	*p_join = '\0';
	return (join);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != c && *str)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
		str[i++] = '\0';
}

void	*ft_calloc(size_t n, size_t size)
{
	char	*str;

	str = malloc(n * size);
	if (!str)
		return (NULL);
	ft_bzero(str, n * size);
	return (str);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}
