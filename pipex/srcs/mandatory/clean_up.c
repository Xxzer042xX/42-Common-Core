/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:16:18 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/13 12:16:18 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de fermeture sécurisée d'un descripteur de fichier.             */
/*                                                                            */
/*   Cette fonction évite les erreurs courantes de fermeture en :             */
/*   1. Vérifiant la validité du descripteur (-1 = invalide)                  */
/*   2. Gérant l'échec potentiel de close()                                   */
/*                                                                            */
/*   Usage dans pipex :                                                       */
/*   - Fermeture des fichiers d'entrée/sortie                                 */
/*   - Fermeture des extrémités de pipes                                      */
/*   - Nettoyage des descripteurs inutilisés                                  */
/*                                                                            */
/*   Paramètre :                                                              */
/*   - fd : descripteur de fichier à fermer                                   */
/*                                                                            */
/* ************************************************************************** */
void	close_fd(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			perror("Warning: Close failed");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de gestion de sortie propre du programme.                       */
/*                                                                            */
/*   Séquence de nettoyage :                                                  */
/*   1. Libération des ressources si data est fourni :                        */
/*      - Fermeture des pipes                                                 */
/*      - Libération de la mémoire                                            */
/*      - Suppression des fichiers temporaires                                */
/*                                                                            */
/*   2. Affichage de l'erreur :                                               */
/*      - Utilise perror pour le message système                              */
/*      - Affiche sur stderr                                                  */
/*                                                                            */
/*   3. Terminaison avec status approprié :                                   */
/*      - ERR_NO_SUCH_FILE                                                    */
/*      - ERR_PERMISSION                                                      */
/*      - ERR_MALLOC                                                          */
/*      - etc.                                                                */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - str : message d'erreur à afficher                                      */
/*   - data : structure à nettoyer (peut être NULL)                           */
/*   - status : code de sortie                                                */
/*                                                                            */
/* ************************************************************************** */
void	ft_exit(char *str, t_pipex *data, int status)
{
	if (data)
		free_parent(data);
	perror(str);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de nettoyage principal du programme.                            */
/*                                                                            */
/*   Nettoyage complet des ressources :                                       */
/*   1. Pipes (pipe_fds) :                                                    */
/*      - N-1 pipes pour N commandes                                          */
/*      - Chaque pipe contient 2 descripteurs [lecture, écriture]             */
/*      Exemple pour 3 commandes :                                            */
/*      cmd1 | cmd2 | cmd3 nécessite 2 pipes                                  */
/*                                                                            */
/*   2. PIDs des processus (cpids) :                                          */
/*      - Tableau des PIDs des processus enfants                              */
/*      - Taille = nombre de commandes                                        */
/*                                                                            */
/*   3. Fichier heredoc :                                                     */
/*      - Supprime .heredoc_tmp si mode heredoc actif                         */
/*      - Évite de laisser des fichiers temporaires                           */
/*                                                                            */
/*   Paramètre :                                                              */
/*   - data : structure contenant toutes les ressources                       */
/*                                                                            */
/* ************************************************************************** */
void	free_parent(t_pipex *data)
{
	int	i;

	if (data->pipe_fds)
	{
		i = 0;
		while (i < data->cmd_count - 1)
		{
			if (data->pipe_fds[i])
				free(data->pipe_fds[i]);
			i++;
		}
		free(data->pipe_fds);
		data->pipe_fds = NULL;
	}
	if (data->cpids)
	{
		free(data->cpids);
		data->cpids = NULL;
	}
	if (data->here_doc)
		unlink(".heredoc_tmp");
}

/* ************************************************************************** */
/*                                                                            */
/*   close_all_pipes:                                                         */
/*   Fonction de fermeture de tous les pipes.                                 */
/*                                                                            */
/*   Pour chaque pipe du pipeline :                                           */
/*   1. Ferme l'extrémité de lecture (pipe[i][0])                             */
/*   2. Ferme l'extrémité d'écriture (pipe[i][1])                             */
/*                                                                            */
/*   Structure des pipes :                                                    */
/*   Pour N commandes :                                                       */
/*   - N-1 pipes numérotés de 0 à N-2                                         */
/*   - pipe[i][0] : lecture pour commande i+1                                 */
/*   - pipe[i][1] : écriture pour commande i                                  */
/*                                                                            */
/*   Paramètre :                                                              */
/*   - data : structure contenant le tableau de pipes                         */
/*                                                                            */
/* ************************************************************************** */
void	close_all_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(data->pipe_fds[i][0]);
		close(data->pipe_fds[i][1]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de libération des tableaux de descripteurs.                     */
/*                                                                            */
/*   Processus de libération :                                                */
/*   1. Libération des sous-tableaux :                                        */
/*      - Parcours descendant des indices                                     */
/*      - Vérifie la validité de chaque pointeur                              */
/*      - Met à NULL après libération                                         */
/*                                                                            */
/*   2. Libération du tableau principal :                                     */
/*      - Après libération de tous les sous-tableaux                          */
/*      - Évite les fuites de mémoire                                         */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - pipe_fds : tableau principal des pipes                                 */
/*   - i : indice maximum (nombre de pipes - 1)                               */
/*                                                                            */
/* ************************************************************************** */
void	free_pipe_fds(int **pipe_fds, int i)
{
	while (i >= 0)
	{
		if (pipe_fds[i])
		{
			free(pipe_fds[i]);
			pipe_fds[i] = NULL;
		}
		i--;
	}
	free(pipe_fds);
}
