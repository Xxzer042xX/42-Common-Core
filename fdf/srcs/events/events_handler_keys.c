/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler_keys.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:24:18 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 21:27:29 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	handle_move(t_app *app, int keycode);
static void	handle_view(t_app *app, int keycode);
static void	change_color(t_app *app, int keycode);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction centrale gère tous les événements clavier de              */
/*   l'application. Elle traite trois catégories de touches :                 */
/*                                                                            */
/*   1. Sortie du programme :                                                 */
/*      - ESC : Déclenche handle_exit                                         */
/*                                                                            */
/*   2. Contrôles de vue (handle_view) :                                      */
/*      - F : Bascule plein écran                                             */
/*      - F1/F2/F3 : Change le mode de vue                                    */
/*      - +/- : Contrôle du zoom                                              */
/*                                                                            */
/*   3. Contrôles de mouvement (handle_move) :                                */
/*      - WASD : Déplacement de la carte                                      */
/*      - Q/E : Rotation                                                      */
/*      - Z/C : Échelle verticale                                             */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - keycode : code de la touche pressée                                    */
/*   - param : pointeur void vers t_app, casté en interne                     */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS pour les opérations normales                                   */
/*   - STATE_KILL si ESC est pressé                                           */
/*                                                                            */
/* ************************************************************************** */
int	handle_key(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		return (handle_exit(app));
	if (keycode == KEY_F || keycode == KEY_PLUS || keycode == KEY_MINUS || \
			keycode == KEY_F1 || keycode == KEY_F2 || keycode == KEY_F3)
		handle_view(app, keycode);
	else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || \
			keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E || \
			keycode == KEY_Y || keycode == KEY_Z || keycode == KEY_C)
		handle_move(app, keycode);
	else if (keycode == KEY_1 || keycode == KEY_2)
		change_color(app, keycode);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère la sortie propre du programme. Elle modifie          */
/*   l'état de l'application pour déclencher l'arrêt.                         */
/*                                                                            */
/*   Processus :                                                              */
/*   1. Change l'état de l'application à STATE_KILL                           */
/*   2. La boucle principale détectera ce changement et terminera             */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*                                                                            */
/*   Retourne:                                                                */
/*   - STATE_KILL : nouvelle valeur de app->state                             */
/*                                                                            */
/* ************************************************************************** */
int	handle_exit(t_app *app)
{
	return (app->state = STATE_KILL);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère les changements de vue et d'affichage de             */
/*   l'application. Elle traite six types d'actions :                         */
/*                                                                            */
/*   1. Changement de projection :                                            */
/*      - F1 : Vue isométrique (VIEW_ISO)                                     */
/*      - F2 : Vue de dessus (VIEW_TOP)                                       */
/*      - F3 : Vue latérale (VIEW_SIDE)                                       */
/*                                                                            */
/*   2. Gestion de la fenêtre :                                               */
/*      - F : Bascule plein écran                                             */
/*                                                                            */
/*   3. Contrôle du zoom :                                                    */
/*      - Plus : Zoom avant (Z_IN)                                            */
/*      - Minus : Zoom arrière (Z_OUT)                                        */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - keycode : code de la touche déclenchant l'action                       */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	handle_view(t_app *app, int keycode)
{
	if (keycode == KEY_F1)
		toggle_view(app, VIEW_ISO);
	if (keycode == KEY_F2)
		toggle_view(app, VIEW_TOP);
	if (keycode == KEY_F3)
		toggle_view(app, VIEW_SIDE);
	if (keycode == KEY_F)
		resize_win(app);
	if (keycode == KEY_PLUS)
		zoom(app, Z_IN);
	if (keycode == KEY_MINUS)
		zoom(app, Z_OUT);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère les déplacements et transformations de la carte.     */
/*   Elle traite trois types de mouvements :                                  */
/*                                                                            */
/*   1. Déplacements (shift_map) :                                            */
/*      - W : Haut    (SHIFT_UP)                                              */
/*      - S : Bas     (SHIFT_DOWN)                                            */
/*      - A : Gauche  (SHIFT_LEFT)                                            */
/*      - D : Droite  (SHIFT_RIGHT)                                           */
/*                                                                            */
/*   2. Rotations (rotate_map) :                                              */
/*      - Q : Gauche  (ROT_LEFT)                                              */
/*      - E : Droite  (ROT_RIGHT)                                             */
/*                                                                            */
/*   3. Échelle verticale (scale_map) :                                       */
/*      - Y/Z : Augmente (SCALE_INCREASE)                                     */
/*      - C : Diminue    (SCALE_DECREASE)                                     */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - keycode : code de la touche déclenchant l'action                       */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	handle_move(t_app *app, int keycode)
{
	if (keycode == KEY_W)
		shift_map(app, SHIFT_UP);
	if (keycode == KEY_A)
		shift_map(app, SHIFT_LEFT);
	if (keycode == KEY_S)
		shift_map(app, SHIFT_DOWN);
	if (keycode == KEY_D)
		shift_map(app, SHIFT_RIGHT);
	if (keycode == KEY_Q)
		rotate_map(app, ROT_LEFT);
	if (keycode == KEY_E)
		rotate_map(app, ROT_RIGHT);
	if (keycode == KEY_Y || keycode == KEY_Z)
		scale_map(app, SCALE_INCREASE);
	if (keycode == KEY_C)
		scale_map(app, SCALE_DECREASE);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère les changements de couleurs des éléments visuels.    */
/*                                                                            */
/*   Options de changement de couleur :                                       */
/*   1. Grille (KEY_1) :                                                      */
/*      - change_grid_color : Cycle à travers les couleurs de la grille       */
/*                                                                            */
/*   2. Barre latérale (KEY_2) :                                              */
/*      - change_sidebar_color : Cycle à travers les couleurs du menu         */
/*                                                                            */
/*   Note : Les deux éléments ont des cycles de couleur indépendants          */
/*   permettant une personnalisation distincte de chaque élément.             */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - keycode : touche pressée (KEY_1 ou KEY_2)                              */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	change_color(t_app *app, int keycode)
{
	if (keycode == KEY_1)
		change_grid_color(app);
	if (keycode == KEY_2)
		change_sidebar_color(app);
}
