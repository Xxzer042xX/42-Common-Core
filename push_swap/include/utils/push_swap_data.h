/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_data.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:20:09 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 11:32:45 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_DATA_H
# define PUSH_SWAP_DATA_H

/* ************************************************************************** */
/*                              DEFAULT VALUES                                */
/* ************************************************************************** */
// Integer limits
# define MAX_INT       2147483647
# define MIN_INT       -2147483648

/* MOVES COST */
# define COST_ROTATE    1
# define COST_SWAP      1
# define COST_PUSH      1

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
