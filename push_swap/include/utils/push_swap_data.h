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
# define MAX_INT       2147483647
# define MIN_INT       -2147483648

//sorted status
# define SORTED         1
# define UNSORTED       0

/* ************************************************************************** */
/*                                      ENUM ERROR                            */
/* ************************************************************************** */
enum e_error
{
	SUCCESS,
	ERR_ARGS,
	ERR_MALLOC,
	ERR_IS_EMPTY,
	ERR_DUP,
	DEBUG
};

/* ************************************************************************** */
/*                            NODE, AND STACK STRUCTURE                       */
/* ************************************************************************** */
typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				value;
	int				index;
}	t_node;

typedef struct s_stack
{
	t_node	*first_node;
	t_node	*last_node;
	int		size;
	char	id_stack;
}	t_stack;

#endif
