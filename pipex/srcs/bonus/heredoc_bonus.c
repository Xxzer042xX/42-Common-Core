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
static int	islimiter(const char *line, const char *limiter);

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
/*   3. Nettoyage :                                                           */
/*      - En cas d'erreur immédiate : unlink + ft_exit                        */
/*      - Nettoyage final via free_parent dans tous les cas                   */
/*                                                                            */
/*   Paramètre :                                                              */
/*   - data : structure contenant le délimiteur et les descripteurs           */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   - Erreur création fichier temporaire : ERR_NO_SUCH_FILE                  */
/*   - Erreur réouverture fichier : ERR_NO_SUCH_FILE                          */
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
/*   3. Trois cas possibles :                                                 */
/*      - Si EOF (Ctrl+D) : ft_exit avec ERR_NO_SUCH_FILE                     */
/*      - Si délimiteur trouvé : ft_exit avec ERR_NO_SUCH_FILE                */
/*      - Sinon : écriture dans fichier temporaire                            */
/*                                                                            */
/*   Nettoyage des ressources :                                               */
/*   - Toute sortie passe par ft_exit qui nettoie via free_parent             */
/*   - Le fichier temporaire est supprimé par unlink dans free_parent         */
/*                                                                            */
/*   Gestion des erreurs :                                                    */
/*   - Sortie systématique via ft_exit pour nettoyage cohérent                */
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
			ft_exit("Heredoc input failed", data, ERR_NO_SUCH_FILE);
		if (islimiter(line, data->limiter))
		{
			free(line);
			ft_exit("Heredoc input failed", data, ERR_NO_SUCH_FILE);
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*   Vérifie si une ligne correspond au délimiteur.                           */
/*                                                                            */
/*   La ligne correspond au délimiteur si :                                   */
/*   1. Elle commence exactement par le délimiteur                            */
/*   2. Est suivie immédiatement par un retour à la ligne (\n)                */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - line : ligne à vérifier                                                */
/*   - limiter : délimiteur à comparer                                        */
/*                                                                            */
/*   Retour :                                                                 */
/*   - 1 si la ligne correspond au délimiteur                                 */
/*   - 0 sinon                                                                */
/*                                                                            */
/* ************************************************************************** */
static int	islimiter(const char *line, const char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	return (!ft_strncmp(line, limiter, len) && line[len] == '\n');
}
