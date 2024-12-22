/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   views_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:44:36 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 09:08:05 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction change le mode de projection de la carte dans l'une       */
/*   des vues définies par l'enum e_views :                                   */
/*   - VIEW_ISO : Vue isométrique (projection à 30 degrés)                    */
/*   - VIEW_TOP : Vue de dessus (projection orthographique)                   */
/*   - VIEW_FRONT : Vue de face (projection latérale)                         */
/*                                                                            */
/*   Le changement de vue s'effectue en trois étapes :                        */
/*   1. Mise à jour du mode de vue dans app->map.view_mode                    */
/*   2. Effacement complet du buffer d'image pour éviter les artéfacts        */
/*      visuels lors du changement de projection                              */
/*   3. Activation du flag needs_update pour forcer un nouveau rendu          */
/*   4. Appel immédiat de render() pour afficher la nouvelle projection       */
/*                                                                            */
/*   Note : Cette fonction est typiquement appelée en réponse aux touches     */
/*   F1, F2, F3 pour basculer entre les différentes vues.                     */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*   - views_mode : constante de l'enum e_views spécifiant la vue désirée     */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	toggle_view(t_app *app, int views_mode)
{
	app->map.view_mode = views_mode;
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}
