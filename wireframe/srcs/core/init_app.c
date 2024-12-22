/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:33:36 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/19 13:43:42 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction initialise l'ensemble de l'application FdF.               */
/*   Elle exécute les étapes d'initialisation dans l'ordre suivant :          */
/*   1. Vérifie la validité du pointeur app                                   */
/*   2. Initialise la matrice de transformation (init_matrix)                 */
/*   3. Initialise la carte (init_map) avec les données du fichier            */
/*   4. Initialise la connexion MLX (init_mlx)                                */
/*   5. Configure les événements (init_event)                                 */
/*   6. Initialise les données de la barre latérale (init_data_sidebar)       */
/*   7. Configure l'état initial de l'application :                           */
/*      - Active le flag de mise à jour (needs_update)                        */
/*      - Définit l'état sur STATE_RUNNING                                    */
/*      - Configure la vue isométrique par défaut                             */
/*                                                                            */
/*   Si une étape échoue, la fonction arrête l'initialisation et retourne     */
/*   immédiatement le code d'erreur approprié.                                */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*   - filename : chemin vers le fichier à traiter                            */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si toutes les étapes d'initialisation réussissent              */
/*   - ERR_DATA si le pointeur app est NULL                                   */
/*   - Code d'erreur spécifique si une des étapes d'initialisation échoue     */
/*                                                                            */
/* ************************************************************************** */
int	init_app(t_app *app, char *filename)
{
	int	status;

	if (!app)
		return (ERR_DATA);
	init_matrix(app);
	status = init_map(app, filename);
	if (status != SUCCESS)
		return (error_exit(status));
	status = init_mlx(app);
	if (status != SUCCESS)
		return (error_exit(status));
	status = init_sidebar(app);
	if (status != SUCCESS)
		return (error_exit(status));
	init_event(app);
	app->needs_update = 1;
	app->state = STATE_RUNNING;
	toggle_view(app, VIEW_ISO);
	return (SUCCESS);
}
