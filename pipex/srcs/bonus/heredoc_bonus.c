/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:29:39 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/14 12:29:42 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	read_heredoc_input(t_pipex *data, int temp_fd);

/* ************************************************************************** */
/*                                                                            */
/*   Gestion du mode heredoc (équivalent de << en shell).                     */
/*                                                                            */
/*   Simule le comportement de la redirection heredoc :                       */
/*   1. Création du fichier temporaire :                                      */
/*      - Nom : .heredoc_tmp                                                  */
/*      - Mode : O_CREAT|O_WRONLY|O_TRUNC (création/écriture/réinitialise)    */
/*      - Permissions : 0644 (rw-r--r--)                                      */
/*                                                                            */
/*   2. Processus :                                                           */
/*      - Lecture des entrées via read_heredoc_input                          */
/*      - Fermeture du fichier temporaire                                     */
/*      - Réouverture en lecture pour le pipeline                             */
/*                                                                            */
/*   3. Nettoyage en cas d'erreur :                                           */
/*      - Suppression du fichier temporaire (unlink)                          */
/*      - Libération des ressources                                           */
/*                                                                            */
/*   Exemple shell équivalent :                                               */
/*   cmd1 << EOF | cmd2                                                       */
/*   ligne1                                                                   */
/*   ligne2                                                                   */
/*   EOF                                                                      */
/*                                                                            */
/*   Paramètre :                                                              */
/*   - data : structure contenant le délimiteur et les descripteurs           */
/*                                                                            */
/* ************************************************************************** */
void	handle_heredoc(t_pipex *data)
{
	int		temp_fd;

	temp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
		ft_exit("Heredoc tmp_file creat failed", data, ERR_NO_SUCH_FILE);
	read_heredoc_input(data, temp_fd);
	close(temp_fd);
	data->infile = open(".heredoc_tmp", O_RDONLY);
	if (data->infile == -1)
	{
		unlink(".heredoc_tmp");
		ft_exit("Heredoc file opening failed", data, ERR_NO_SUCH_FILE);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Lecture interactive des entrées du heredoc.                              */
/*                                                                            */
/*   Processus de lecture :                                                   */
/*   1. Affichage du prompt "heredoc> "                                       */
/*   2. Lecture ligne par ligne (get_next_line)                               */
/*   3. Comparaison avec le délimiteur :                                      */
/*      - Si ligne == délimiteur + '\n' : fin de lecture                      */
/*      - Si ligne == NULL (Ctrl+D) : fin de lecture                          */
/*      - Sinon : écriture dans le fichier temporaire                         */
/*                                                                            */
/*   Gestion des entrées :                                                    */
/*   - Conserve les retours à la ligne (\n)                                   */
/*   - Pas d'interprétation des caractères spéciaux                           */
/*   - Support de Ctrl+D pour terminer l'entrée                               */
/*                                                                            */
/*   Exemple d'utilisation :                                                  */
/*   heredoc> Première ligne                                                  */
/*   heredoc> Deuxième ligne                                                  */
/*   heredoc> EOF (délimiteur)                                                */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant le délimiteur (data->limiter)               */
/*   - temp_fd : descripteur du fichier temporaire                            */
/*                                                                            */
/* ************************************************************************** */
static void	read_heredoc_input(t_pipex *data, int temp_fd)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) && \
			line[ft_strlen(data->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
}
