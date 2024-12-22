/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:44:49 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 14:14:40 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	remake_window(t_app *app);
static void	resize_sidebar(t_app *app);
static int	setup_new_window(t_app *app);
static void	center_map(t_app *app);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction bascule la fenêtre entre mode normal et plein écran.      */
/*                                                                            */
/*   Comportement :                                                           */
/*   - Si fenêtre en taille normale (INIT_WIN_W/H) : passe en plein écran     */
/*   - Si fenêtre en plein écran : retourne à la taille normale               */
/*                                                                            */
/*   Note : Le changement de taille déclenche un redessin complet de          */
/*   l'interface et réinitialise la position de la vue.                       */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS : le changement de taille s'est effectué correctement          */
/*                                                                            */
/* ************************************************************************** */
int	resize_win(t_app *app)
{
	if (app->win.w_win == INIT_WIN_W && app->win.h_win == INIT_WIN_H)
	{
		app->win.w_win = MAX_WIN_W;
		app->win.h_win = MAX_WIN_H;
	}
	else
	{
		app->win.w_win = INIT_WIN_W;
		app->win.h_win = INIT_WIN_H;
	}
	remake_window(app);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction redimensionne la fenêtre aux dimensions spécifiées en     */
/*   suivant ces étapes :                                                     */
/*                                                                            */
/*   1. Nettoyage des ressources existantes :                                 */
/*      - Destruction de l'image MLX actuelle                                 */
/*      - Destruction de la fenêtre actuelle                                  */
/*      - En cas d'échec : nettoyage complet et sortie avec ERR_MLX           */
/*                                                                            */
/*   2. Mise à jour des paramètres :                                          */
/*      - Nouvelles dimensions de fenêtre                                     */
/*      - Réinitialisation des décalages (shift_x/y à 0)                      */
/*                                                                            */
/*   3. Recréation des éléments :                                             */
/*      - Nouvelle fenêtre et image (setup_new_window)                        */
/*      - Redimensionnement de la barre latérale                              */
/*      - Réinitialisation des événements                                     */
/*                                                                            */
/*   4. Mise à jour de l'affichage :                                          */
/*      - Activation du flag needs_update                                     */
/*      - Rendu immédiat de la nouvelle vue                                   */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - new_width : nouvelle largeur en pixels                                 */
/*   - new_height : nouvelle hauteur en pixels                                */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	remake_window(t_app *app)
{
	mlx_destroy_image(app->win.mlx, app->win.img);
	mlx_destroy_window(app->win.mlx, app->win.win);
	setup_new_window(app);
	resize_sidebar(app);
	center_map(app);
	init_event(app);
	app->needs_update = 1;
	render(app);
}

static void	center_map(t_app *app)
{
	app->matrix.shift_x = 0;
	app->matrix.shift_y = 0;
	if (app->win.w_win == INIT_WIN_W && app->win.h_win == INIT_WIN_H)
		app->matrix.scale = SCALE;
	else
		app->matrix.scale = 2.5 * SCALE;
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction crée une nouvelle fenêtre MLX et configure ses            */
/*   paramètres graphiques.                                                   */
/*                                                                            */
/*   Processus d'initialisation :                                             */
/*   1. Création de la fenêtre MLX avec les dimensions spécifiées             */
/*      - Utilisation du titre définit par TITLE                              */
/*                                                                            */
/*   2. Création d'une nouvelle image MLX                                     */
/*      - Dimensions adaptées à la taille de la fenêtre                       */
/*                                                                            */
/*   3. Configuration du buffer d'image                                       */
/*      - Récupération de l'adresse du buffer                                 */
/*      - Initialisation des paramètres (bbp, line_len, endian)               */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   - Vérification de la création de la fenêtre                              */
/*   - Vérification de la création de l'image                                 */
/*   - Vérification de l'accès au buffer                                      */
/*   En cas d'échec : nettoyage des ressources et sortie avec ERR_MLX         */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si l'initialisation est réussie                                */
/*                                                                            */
/* ************************************************************************** */
static int	setup_new_window(t_app *app)
{
	int	new_width;
	int	new_height;

	new_width = app->win.w_win;
	new_height = app->win.h_win;
	app->win.win = mlx_new_window(app->win.mlx, new_width, new_height, TITLE);
	if (!app->win.win)
	{
		cleanup_app(app);
		exit(error_exit(ERR_MLX));
	}
	app->win.img = mlx_new_image(app->win.mlx, app->win.w_win, app->win.h_win);
	if (app->win.img == NULL)
	{
		cleanup_app(app);
		exit(error_exit(ERR_MLX));
	}
	app->win.addr = mlx_get_data_addr(app->win.img, &app->win.bbp, \
								&app->win.line_len, &app->win.endian);
	if (app->win.addr == NULL)
	{
		cleanup_app(app);
		exit(error_exit(ERR_MLX));
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction adapte la barre latérale aux nouvelles dimensions de      */
/*   la fenêtre. Le comportement diffère selon le mode :                      */
/*                                                                            */
/*   Mode normal (INIT_WIN_W/H) :                                             */
/*   - Largeur = 1/4 de la fenêtre                                            */
/*   - Espacements standards (PADDING_X/Y, SPACE_TITLE/CTRL)                  */
/*                                                                            */
/*   Mode plein écran :                                                       */
/*   - Largeur = 1/10 de la fenêtre                                           */
/*   - Espacements adaptés à la nouvelle taille                               */
/*   - Espacement vertical mis à l'échelle (scale_y)                          */
/*                                                                            */
/*   Paramètres ajustés :                                                     */
/*   - Dimensions (width, height)                                             */
/*   - Position (x_pos, y_pos)                                                */
/*   - Marges (x_offset, y_offset)                                            */
/*   - Espacements (y_space_title, y_space_ctrl)                              */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - new_width : nouvelle largeur de la fenêtre                             */
/*   - new_height : nouvelle hauteur de la fenêtre                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	resize_sidebar(t_app *app)
{
	int	new_width;
	int	new_height;
	int	scale_y;

	new_width = app->win.w_win;
	new_height = app->win.h_win;
	if (new_width == INIT_WIN_W && new_height == INIT_WIN_H)
	{
		app->sidebar.height = INIT_WIN_H;
		app->sidebar.x_offset = PADDING_OF_X;
		app->sidebar.y_space_ctrl = SPACE_CTRL;
	}
	else
	{
		scale_y = new_height / INIT_WIN_H;
		app->sidebar.height = new_height;
		app->sidebar.x_offset = PADDING_OF_X + PADDING_X;
		app->sidebar.y_space_ctrl = SPACE_CTRL * scale_y;
	}
}
