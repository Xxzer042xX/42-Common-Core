/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:57 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/13 12:06:57 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}

char	*read_file(int fd, char *storage)
{
	char	*joined_str;
	char	*temp_buffer;
	int		byte_read;

	if (!storage)
		storage = ft_calloc(1, 1);
	if (!storage)
		return (NULL);
	temp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (free(storage), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(temp_buffer), free(storage), NULL);
		temp_buffer[byte_read] = '\0';
		joined_str = ft_strjoin(storage, temp_buffer);
		free(storage);
		storage = joined_str;
		if (!storage || ft_strchr(temp_buffer, '\n'))
			break ;
	}
	return (free(temp_buffer), storage);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	line = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!line)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		line[j++] = str[i++];
	return (free(str), line);
}
