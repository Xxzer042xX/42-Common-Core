/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:12:28 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 20:33:16 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction initialise la matrice de transformation avec les          */
/*   paramètres par défaut suivants :                                         */
/*   - space : Espacement entre les points (SPACE)                            */
/*   - iso_angle : Angle pour la projection isométrique (ISO_ANGLE)           */
/*   - zoom : Facteur de zoom initial (Z_DEFAULT)                             */
/*   - scale : Facteur d'échelle global (SCALE)                               */
/*                                                                            */
/*   Ces paramètres sont stockés dans la sous-structure matrix de app         */
/*   et sont utilisés pour :                                                  */
/*   - Définir la distance entre les points de la grille (space)              */
/*   - Configurer l'angle de la vue isométrique (iso_angle)                   */
/*   - Définir le niveau de zoom initial de la vue (zoom)                     */
/*   - Ajuster l'échelle globale du modèle (scale)                            */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*          contenant la sous-structure matrix pour les transformations       */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*   Note : La fonction suppose que le pointeur app est valide                */
/*                                                                            */
/* ************************************************************************** */
void	init_matrix(t_app *app)
{
	app->matrix.space = SPACE;
	app->matrix.iso_angle = ISO_ANGLE;
	app->matrix.zoom = Z_DEFAULT;
	app->matrix.scale = SCALE;
}
