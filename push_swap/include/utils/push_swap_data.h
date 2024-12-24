/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_data.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:20:09 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/24 21:20:09 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_DATA_H
# define PUSH_SWAP_DATA_H

/* ************************************************************************** */
/*                              DEFAULT VALUES                                */
/* ************************************************************************** */
// Stack limits for sort selection
# define SMALL_SORT    3
# define MID_SORT      5
# define BIG_SORT      100

// Integer limits
# define MAX_INT       2147483647
# define MIN_INT       -2147483648

/* MOVES COST */
# define COST_ROTATE    1
# define COST_SWAP      1
# define COST_PUSH      1

/* ************************************************************************** */
/*                              OWN LIB                                       */
/* ************************************************************************** */
# include "../lib/libftprintf/include/ft_printf.h"
# include "../lib/libftprintf/libft/libft.h"


/* ************************************************************************** */
/*                                      ENUM ERROR                            */
/* ************************************************************************** */

enum e_error
{
	SUCCESS,
	ERR_ARGS,
	ERR_MALLOC,
	ERR_DATA,
	ERR_FILE,
	ERR_FORMAT,
	DEBUG
};

/* ************************************************************************** */
/*                  NODE, MOVE CALCULATION, AND STACK STRUCTURE               */
/* ************************************************************************** */
// Node structure for linked list
typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

// Stack structure with metadata
typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
	char	id;    // 'a' or 'b' for debugging
}	t_stack;

// Move calculation structure
typedef struct s_move
{
	int	cost;      // Total cost of operation
	int	target;    // Target value to move
	int	steps;     // Number of steps needed
}	t_move;

#endif
