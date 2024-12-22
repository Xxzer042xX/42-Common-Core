/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:29:19 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 21:10:59 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction centrale gère le cycle de rendu de l'application FdF.     */
/*   Elle est appelée en continu par la boucle MLX et coordonne               */
/*   l'affichage de tous les éléments visuels.                                */
/*                                                                            */
/*   Séquence de rendu :                                                      */
/*   1. Vérification de l'état :                                              */
/*      - Si STATE_KILL : termine la boucle MLX                               */
/*      - Si !needs_update : aucun rendu nécessaire                           */
/*                                                                            */
/*   2. Rendu des éléments graphiques (si needs_update) :                     */
/*      - Dessine la carte wireframe (draw_map)                               */
/*      - Dessine le fond de la barre latérale (draw_sidebar)                 */
/*      - Transfère l'image complète vers la fenêtre                          */
/*                                                                            */
/*   3. Rendu du texte et des informations :                                  */
/*      - Affiche les contrôles dans la barre latérale                        */
/*      - Affiche les valeurs en temps réel                                   */
/*      - Utilise la position y retournée par print_controls                  */
/*                                                                            */
/*   4. Réinitialisation :                                                    */
/*      - Désactive le flag needs_update                                      */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant :                */
/*          * L'état de l'application (state)                                 */
/*          * Les ressources MLX (win)                                        */
/*          * Le flag de mise à jour (needs_update)                           */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS (0) dans tous les cas                                          */
/*     Note : La valeur de retour n'est pas utilisée par MLX                  */
/*                                                                            */
/* ************************************************************************** */
int	render(t_app *app)
{
	if (app->state == STATE_KILL)
		mlx_loop_end(app->win.mlx);
	if (!app->needs_update)
		return (SUCCESS);
	draw_map(app);
	draw_sidebar(app);
	mlx_put_image_to_window(app->win.mlx, app->win.win, app->win.img, 0, 0);
	print_sidebar_content(app);
	app->needs_update = 0;
	return (SUCCESS);
}
