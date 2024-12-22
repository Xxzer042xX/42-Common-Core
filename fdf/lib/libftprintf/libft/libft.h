/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:17:47 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/12/18 20:12:17 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define OPEN_MAX 256

//alias for ULL
typedef unsigned long long	t_ull;

/* ************************************************************************** */
/*                     Fonctions de Manipulation de Chaines                   */
/* ************************************************************************** */
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//vip
char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);
int		count_line(const char *filename);
void	ft_free_split(char **split, int i);

/* ************************************************************************** */
/*                           Fonctions de Conversion                          */
/* ************************************************************************** */
int		ft_atoi(const char *nptr);
int		ft_atoi_base(const char *nptr, int base);
char	*ft_itoa(int n);
int		ft_tolower(int c);
int		ft_toupper(int c);
//vip
char	*ft_itoa_base(unsigned long long value, int base, int is_upper);
char	*ft_ulltoa(unsigned long long n);
t_ull	ft_ulllen(unsigned long long n);
int		ft_intlen(int n);

/* ************************************************************************** */
/*                       Fonctions de Gestion de Mémoire                      */
/* ************************************************************************** */
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/* ************************************************************************** */
/*                           Fonctions d'Affichage                            */
/* ************************************************************************** */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
//vip
int		ft_putstr_check_ret(char *str);
int		ft_putchar_check_ret(char c);

/* ************************************************************************** */
/*                         Fonctions de Vérification                          */
/* ************************************************************************** */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
//vip
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isflags(int c);
int		ft_ishexa(const char *str);

/* ************************************************************************** */
/*                        Structures et Fonctions Bonus                       */
/* ************************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *news);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *news);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
