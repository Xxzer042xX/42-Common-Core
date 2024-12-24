/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:45:30 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/27 01:58:27 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# ifdef __APPLE__
#  define NULL_POINTER "0x0"
# elif __linux__
#  define NULL_POINTER "(nil)"
# else
#  error "Unsupported platform. This code is only for Linux and macOS."

# endif

typedef struct s_flags
{
	char	*join;
	int		minus;
	int		zero;
	int		dot;
	int		star;
	int		width;
	int		prec;
	int		plus;
	int		space;
	int		hash;
	int		is_nega;
	int		is_null;
	int		is_uintx;
}	t_flags;

/* ************************************************************************** */
/*                     Fonctions principale                                   */
/* ************************************************************************** */

int		ft_printf(const char *format, ...);

/* ************************************************************************** */
/*                     Fonctions de Manipulation de format                    */
/* ************************************************************************** */

int		ft_print_char(va_list args, t_flags *flags);
int		ft_print_str(va_list args, t_flags *flags);
int		ft_print_int(va_list args, t_flags *flags);
int		ft_print_uint(va_list args, t_flags *flags);
int		ft_print_hex(va_list args, t_flags *flags, char specifier);
int		ft_print_pointer(va_list args, t_flags *flags);

/* ************************************************************************** */
/*                             Sous Fonctions                                 */
/* ************************************************************************** */

int		ft_parsing(const char **format, va_list args, t_flags *flags);
int		ft_print_str_padding(int padding);
int		ft_print_str_prec(char *str, int prec);
int		ft_pad_int(int padding, char c);
int		ft_print_sign(t_flags *flags, int *count);
int		ft_int_minus(t_flags *flags, int to_print, int *n);
int		ft_int_dot(t_flags *flags, int to_print, int *n);
int		ft_int_width(t_flags *flags, int to_print, int *n);

#endif
