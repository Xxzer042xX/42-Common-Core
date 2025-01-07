/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:00:49 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/05 19:19:02 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                              EXEMPLE 1: PIPE SIMPLE                          */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main: Démontre l'utilisation basique d'un pipe
** - Crée un pipe
** - Écrit un message dans le pipe
** - Lit le message depuis le pipe
** - Gère les erreurs et libère les ressources
*/
int	main(int argc, char **argv)
{
	int			pipefd[2];
	const char	message[] = "Hello through pipe!";
	char		buffer[30];

	(void)argc;
	(void)argv;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	write(pipefd[1], message, strlen(message));
	read(pipefd[0], buffer, strlen(message));
	buffer[strlen(message)] = '\0';
	printf("Lu depuis le pipe : %s\n", buffer);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
