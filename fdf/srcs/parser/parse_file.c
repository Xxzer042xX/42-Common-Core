/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:39:43 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/17 21:57:35 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	parse_line(t_app *app, char *line, int num_line);
static int	save_points_on_database(t_app *app, char **tokens, int num_line);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction effectue le parsing complet du fichier FdF en suivant     */
/*   ces étapes :                                                             */
/*                                                                            */
/*   1. Ouverture et vérification du fichier :                                */
/*      - Ouvre le fichier en lecture seule                                   */
/*      - Vérifie que la première ligne existe                                */
/*                                                                            */
/*   2. Lecture séquentielle :                                                */
/*      - Lit chaque ligne avec get_next_line                                 */
/*      - Ignore les lignes vides (contenant uniquement '\n')                 */
/*      - Envoie les lignes valides à parse_line                              */
/*                                                                            */
/*   3. Gestion des erreurs :                                                 */
/*      - Libère la mémoire en cas d'erreur                                   */
/*      - Ferme le descripteur de fichier dans tous les cas                   */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - filename : chemin du fichier à parser                                  */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si le fichier est complètement parsé                           */
/*   - ERR_FILE si erreur d'ouverture ou lecture                              */
/*                                                                            */
/* ************************************************************************** */
int	parse_file(t_app *app, char *filename)
{
	int		status;
	int		num_line;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ERR_FILE);
	num_line = 0;
	while (line)
	{
		if (*line != '\n')
		{
			status = parse_line(app, line, num_line);
			if (status != SUCCESS)
				return (close(fd), free(line), status);
			num_line++;
		}
		free (line);
		line = get_next_line(fd);
	}
	return (close(fd), SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction parse une ligne du fichier FdF en plusieurs étapes :      */
/*                                                                            */
/*   1. Nettoyage et tokenisation :                                           */
/*      - Supprime le retour chariot (\n) avec ft_strtrim                     */
/*      - Découpe la ligne en tokens selon les espaces                        */
/*                                                                            */
/*   2. Validation de la largeur :                                            */
/*      - Compte le nombre de tokens (largeur)                                */
/*      - Si première ligne : définit la largeur de référence                 */
/*      - Sinon : vérifie la cohérence avec la largeur de référence           */
/*                                                                            */
/*   3. Allocation et sauvegarde :                                            */
/*      - Alloue un tableau de t_point pour la ligne                          */
/*      - Appelle save_points_on_database pour remplir les données            */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - line : ligne brute du fichier                                          */
/*   - num_line : index de la ligne courante                                  */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS en cas de réussite                                             */
/*   - ERR_MALLOC si échec d'allocation                                       */
/*   - ERR_FORMAT si largeur invalide                                         */
/*   - ERR_DATA si erreur dans les données                                    */
/*                                                                            */
/* ************************************************************************** */
static int	parse_line(t_app *app, char *line, int num_line)
{
	char	**tokens;
	int		width;
	char	*clear_line;

	clear_line = ft_strtrim(line, "\n");
	if (!clear_line)
		return (ERR_MALLOC);
	tokens = ft_split(clear_line, ' ');
	free (clear_line);
	if (!tokens)
		return (ERR_MALLOC);
	width = 0;
	while (tokens[width])
		width++;
	if (num_line == 0)
		app->map.w_map = width;
	else if (width != app->map.w_map)
		return (ft_free_split(tokens, width), ERR_FORMAT);
	app->map.points[num_line] = malloc(sizeof(t_point) * width);
	if (!app->map.points[num_line])
		return (ft_free_split(tokens, width), ERR_MALLOC);
	ft_memset(app->map.points[num_line], 0, sizeof(t_point) * width);
	if (save_points_on_database(app, tokens, num_line) != SUCCESS)
		return (ft_free_split(tokens, width), ERR_DATA);
	return (ft_free_split(tokens, width), SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction convertit les tokens en points dans la structure map.     */
/*   Pour chaque token de la ligne, elle :                                    */
/*                                                                            */
/*   1. Extraction des données :                                              */
/*      - Appelle parsing_z pour extraire la hauteur et la couleur            */
/*      - Vérifie que le format des données est valide                        */
/*                                                                            */
/*   2. Initialisation des coordonnées :                                      */
/*      - Définit x comme l'index de la colonne                               */
/*      - Définit y comme le numéro de ligne                                  */
/*                                                                            */
/*   3. Validation :                                                          */
/*      - Vérifie que l'index ne dépasse pas la largeur de la carte           */
/*      - S'assure que le token n'est pas une ligne vide                      */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - tokens : tableau des valeurs tokenisées de la ligne                    */
/*   - num_line : index de la ligne en cours de traitement                    */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si tous les points sont correctement sauvegardés               */
/*   - ERR_FORMAT si le format des données est invalide                       */
/*                                                                            */
/* ************************************************************************** */
static int	save_points_on_database(t_app *app, char **tokens, int num_line)
{
	int	col;

	col = 0;
	while (tokens[col] && tokens[col][0] != '\n' && col < app->map.w_map)
	{
		if (parsing_z(app, tokens[col], num_line, col) != SUCCESS)
			return (ERR_FORMAT);
		app->map.points[num_line][col].pos.x = col;
		app->map.points[num_line][col].pos.y = num_line;
		col++;
	}
	return (SUCCESS);
}
