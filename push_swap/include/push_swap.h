/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:30:31 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 23:51:57 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ************************************************************************** */
/*                              OWN LIB                                       */
/* ************************************************************************** */
# include "../lib/libftprintf/include/ft_printf.h"
# include "../lib/libftprintf/libft/libft.h"

/* ************************************************************************** */
/*                              HEADER UTILS                                  */
/* ************************************************************************** */
# include "utils/push_swap_data.h"

/* ************************************************************************** */
/*                             STANDAR LIB                                    */
/* ************************************************************************** */
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                             CORE FUNCTIONS                                 */
/* ************************************************************************** */
int		init_stack(char id, t_stack **stack);
int		cleanup(t_stack *a, t_stack *b, int status);
void	print_error(int error);

/* ************************************************************************** */
/*                              STACK OPERATIONS                              */
/* ************************************************************************** */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* ************************************************************************** */
/*                             PUSH_SWAP UTILS                                */
/* ************************************************************************** */
int		is_sorted(t_stack *stack);
void 	index_stack(t_stack *stack);
void	choose_algo(t_stack *a, t_stack *b);

/* ************************************************************************** */
/*                                 PARSING                                    */
/* ************************************************************************** */
int		parse_args(int ac, char **av, t_stack *a);
//utils
int		handle_numbers(t_stack *stack, char **numbers);
int		process_number(t_stack *stack, const char *str);

/* ************************************************************************** */
/*                                   SORT                                     */
/* ************************************************************************** */
void	sort_three(t_stack *a);
void	sort_four(t_stack *a, t_stack *b);
void	sort_five(t_stack *a, t_stack *b);
void	sort_big(t_stack *a, t_stack *b);

#endif