/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:30:31 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/24 20:30:31 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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
/*                              CORE                                          */
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
/*                              UTILS                                         */
/* ************************************************************************** */
t_stack	*init_stack(char id);
t_stack	*parse_args(int ac, char **av);
void	free_stack(t_stack *stack);
int		error_exit(int error);
void	cleanup_app(t_stack *a, t_stack *b);

/* ************************************************************************** */
/*                               ALGORITHMS                                   */
/* ************************************************************************** */
void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	sort_big(t_stack *a, t_stack *b);
int		is_sorted(t_stack *stack);
void	choose_algo(t_stack *a, t_stack *b);
int		get_min(t_stack *stack);
int		get_max(t_stack *stack);

#endif