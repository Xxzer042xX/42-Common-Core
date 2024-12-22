/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:55:50 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 19:36:08 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *news)
{
	t_list	*last;

	if (!news)
		return ;
	if (!*lst)
	{
		*lst = news;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = news;
}
