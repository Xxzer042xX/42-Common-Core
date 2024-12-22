/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:59 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 19:59:47 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_file(int fd, char *static_buffer);
static char	*ft_extract_line(char *static_buffer);
static char	*ft_next(char *str);
static int	init_buffer(char **static_buffer);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction principale implémente la lecture ligne par ligne d'un     */
/*   fichier en utilisant un buffer statique pour gérer les lectures          */
/*   partielles.                                                              */
/*                                                                            */
/*   Processus de lecture :                                                   */
/*   1. Vérifications initiales :                                             */
/*      - Validité du descripteur de fichier                                  */
/*      - Taille du buffer positive                                           */
/*      - Permissions de lecture (read)                                       */
/*                                                                            */
/*   2. Gestion du buffer statique :                                          */
/*      - Un buffer par descripteur de fichier (tableau OPEN_MAX)             */
/*      - Nettoyage automatique en cas d'erreur                               */
/*                                                                            */
/*   3. Séquence d'opérations :                                               */
/*      - Lecture et accumulation via read_file                               */
/*      - Extraction de la ligne via ft_extract_line                          */
/*      - Préparation du buffer suivant via ft_next                           */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - fd : descripteur de fichier valide (0 ≤ fd < OPEN_MAX)                 */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Ligne lue (avec \n si présent)                                         */
/*   - NULL si :                                                              */
/*     * Fin de fichier atteinte                                              */
/*     * Erreur de lecture                                                    */
/*     * Paramètres invalides                                                 */
/*                                                                            */
/* ************************************************************************** */
char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if ((fd >= 0 && fd < OPEN_MAX) && buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	extracted_line = ft_extract_line(buffer[fd]);
	if (!extracted_line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_next(buffer[fd]);
	return (extracted_line);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction effectue la lecture physique du fichier et accumule       */
/*   les données dans le buffer statique.                                     */
/*                                                                            */
/*   Processus de lecture :                                                   */
/*   1. Initialisation du buffer si nécessaire                                */
/*   2. Allocation du buffer temporaire (BUFFER_SIZE + 1)                     */
/*   3. Lecture en boucle jusqu'à :                                           */
/*      - Rencontrer un \n                                                    */
/*      - Atteindre EOF                                                       */
/*      - Erreur de lecture                                                   */
/*   4. Concaténation des lectures dans le buffer statique                    */
/*                                                                            */
/*   Gestion mémoire :                                                        */
/*   - Libération systématique des buffers temporaires                        */
/*   - Gestion des erreurs d'allocation                                       */
/*   - Protection contre les fuites mémoire                                   */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - fd : descripteur de fichier                                            */
/*   - static_buffer : buffer persistant entre les appels                     */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Buffer mis à jour contenant les nouvelles données                      */
/*   - NULL si erreur (lecture ou allocation)                                 */
/*                                                                            */
/* ************************************************************************** */
static char	*read_file(int fd, char *static_buffer)
{
	char	*temp_buffer;
	char	*remake_file;
	int		byte_read;

	if (!static_buffer)
		if (!init_buffer(&static_buffer))
			return (NULL);
	temp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (free(static_buffer), NULL);
	byte_read = 1;
	while (!ft_strchr(static_buffer, '\n') && byte_read > 0)
	{
		byte_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(temp_buffer), free(static_buffer), NULL);
		temp_buffer[byte_read] = '\0';
		remake_file = ft_strjoin(static_buffer, temp_buffer);
		free(static_buffer);
		if (!remake_file)
			return (free(temp_buffer), NULL);
		static_buffer = remake_file;
	}
	return (free(temp_buffer), static_buffer);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction initialise le buffer statique avec une chaîne vide.       */
/*                                                                            */
/*   Processus d'initialisation :                                             */
/*   1. Allocation d'un octet unique initialisé à 0                           */
/*   2. Vérification du succès de l'allocation                                */
/*                                                                            */
/*   Usage :                                                                  */
/*   - Appelée lors de la première lecture d'un descripteur                   */
/*   - Garantit un état initial cohérent du buffer                            */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - static_buffer : pointeur double vers le buffer à initialiser           */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si l'allocation réussit                                        */
/*   - ERR_MALLOC en cas d'échec d'allocation                                 */
/*                                                                            */
/* ************************************************************************** */
static int	init_buffer(char **static_buffer)
{
	*static_buffer = ft_calloc(1, 1);
	if (!static_buffer)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction extrait une ligne complète du buffer statique,            */
/*   en incluant le caractère newline s'il est présent.                       */
/*                                                                            */
/*   Algorithme d'extraction :                                                */
/*   1. Vérification du contenu du buffer                                     */
/*   2. Calcul de la longueur de la ligne jusqu'à \n ou \0                    */
/*   3. Allocation de la mémoire pour la ligne                                */
/*   4. Copie des caractères avec gestion spéciale du \n                      */
/*                                                                            */
/*   Particularités :                                                         */
/*   - Inclut le \n dans la ligne si présent                                  */
/*   - Gère correctement les lignes sans \n (fin de fichier)                  */
/*   - Vérifie la validité du buffer d'entrée                                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - static_buffer : buffer contenant les données accumulées                */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Ligne extraite (avec \n si présent)                                    */
/*   - NULL si buffer vide ou erreur d'allocation                             */
/*                                                                            */
/* ************************************************************************** */
static char	*ft_extract_line(char *static_buffer)
{
	char	*extracted_line;
	int		i;

	i = 0;
	if (!static_buffer[i])
		return (NULL);
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (static_buffer[i] == '\n')
		i++;
	extracted_line = ft_calloc(i + 1, sizeof(char));
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
	{
		extracted_line[i] = static_buffer[i];
		i++;
	}
	if (static_buffer[i] == '\n')
		extracted_line[i] = '\n';
	return (extracted_line);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction prépare le buffer statique pour la prochaine lecture      */
/*   en supprimant la ligne extraite et en préservant le reste.               */
/*                                                                            */
/*   Processus de mise à jour :                                               */
/*   1. Localisation de la fin de la ligne extraite (\n ou \0)                */
/*   2. Allocation d'un nouveau buffer pour les données restantes             */
/*   3. Copie des caractères restants au début du nouveau buffer              */
/*   4. Libération de l'ancien buffer                                         */
/*                                                                            */
/*   Gestion mémoire :                                                        */
/*   - Libère l'ancien buffer dans tous les cas                               */
/*   - Gère le cas où il n'y a plus de données à conserver                    */
/*   - Protège contre les fuites mémoire                                      */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - str : buffer contenant la ligne extraite et les données restantes      */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Nouveau buffer avec les données restantes                              */
/*   - NULL si plus de données ou erreur d'allocation                         */
/*                                                                            */
/* ************************************************************************** */
static char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	i++;
	line = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!line)
		return (free(str), NULL);
	j = 0;
	while (str[i])
		line[j++] = str[i++];
	free(str);
	return (line);
}
