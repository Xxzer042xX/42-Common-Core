/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sidebar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:39:31 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 19:01:55 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	init_ctrl_pairs(t_app *app);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction initialise les données de la barre latérale (sidebar)     */
/*   qui affiche les contrôles de l'application. Elle configure :             */
/*                                                                            */
/*   1. Paramètres de base de la sidebar :                                    */
/*      - Titre ("FdF Controls:")                                             */
/*      - Dimensions (largeur = 1/4 de la fenêtre, hauteur = fenêtre)         */
/*      - Espacements (y_offset, x_offset)                                    */
/*      - Position (x_pos, y_pos)                                             */
/*      - Espacements entre éléments (y_space_title, y_space_ctrl)            */
/*                                                                            */
/*   2. Contrôles de l'interface :                                            */
/*      - Alloue un tableau de 6 paires de contrôles                          */
/*      - Initialise les paires action/touche :                               */
/*        * Déplacement (Move: wasd)                                          */
/*        * Rotation (Rotate: Q/E)                                            */
/*        * Vue (View: F1,2,3)                                                */
/*        * Plein écran (Full Scr: f)                                         */
/*        * Zoom (Zoom: Wheel)                                                */
/*        * Échelle (Scale: z/c)                                              */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*          contenant la sous-structure sidebar                               */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si l'initialisation est réussie                                */
/*   - ERR_MALLOC si l'allocation du tableau de contrôles échoue              */
/*                                                                            */
/*   Note: Utilise des constantes définies (INIT_WIN_W/H, PADDING_*)          */
/*   pour les dimensions et espacements                                       */
/*                                                                            */
/* ************************************************************************** */
int	init_sidebar(t_app *app)
{
	app->sidebar.title = "Controls:";
	app->sidebar.color.hex = GREY_50;
	app->sidebar.width = 180;
	app->sidebar.height = INIT_WIN_H;
	app->sidebar.y_offset = PADDING_OF_Y;
	app->sidebar.x_offset = PADDING_OF_X;
	app->sidebar.x_pos = PADDING_X;
	app->sidebar.y_pos = PADDING_Y;
	app->sidebar.y_space_title = SPACE_TITLE;
	app->sidebar.y_space_ctrl = SPACE_CTRL;
	return (init_ctrl_pairs(app));
}

static int	init_ctrl_pairs(t_app *app)
{
	app->sidebar.title = "Controls:";
	app->sidebar.ctrl_pairs = malloc(sizeof(t_control_pair) * 7);
	if (!app->sidebar.ctrl_pairs)
		return (ERR_MALLOC);
	app->sidebar.ctrl_count = 7;
	app->sidebar.ctrl_pairs[0] = (t_control_pair){"Move:", "W | A | S | D"};
	app->sidebar.ctrl_pairs[1] = (t_control_pair){"View:", "F1 | F2 | F3"};
	app->sidebar.ctrl_pairs[2] = (t_control_pair){"Zoom:", "Wheel | + / -"};
	app->sidebar.ctrl_pairs[3] = (t_control_pair){"Rotate:", "Q | E"};
	app->sidebar.ctrl_pairs[4] = (t_control_pair){"Colors:", "1 | 2"};
	app->sidebar.ctrl_pairs[5] = (t_control_pair){"Scale:", "Z | C"};
	app->sidebar.ctrl_pairs[6] = (t_control_pair){"Full Scr:", "F"};
	return (SUCCESS);
}
