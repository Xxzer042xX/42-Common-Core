/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:07:18 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/13 12:07:18 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define OPEN_MAX 1024

/* ************************************************************************** */
/*                            Fonctions main                                  */
/* ************************************************************************** */

char	*get_next_line(int fd);

/* ************************************************************************** */
/*                            Fonctions aux                                   */
/* ************************************************************************** */

char	*read_file(int fd, char *storage);
char	*ft_line(char *str);
char	*ft_next(char *str);

/* ************************************************************************** */
/*                            Fonctions utils                                 */
/* ************************************************************************** */

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t n, size_t size);
size_t	ft_strlen(const char *str);

#endif