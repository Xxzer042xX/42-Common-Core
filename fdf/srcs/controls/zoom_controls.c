/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:49:12 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/16 15:18:55 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction modifie le niveau de zoom de la carte en utilisant        */
/*   un facteur multiplicateur.                                               */
/*                                                                            */
/*   Fonctionnement :                                                         */
/*   1. Multiplie le zoom actuel (matrix.zoom) par le facteur fourni          */
/*   2. Efface le contenu actuel de l'image (mise à zéro du buffer)           */
/*   3. Active le flag de mise à jour (needs_update)                          */
/*   4. Déclenche un nouveau rendu avec le zoom modifié                       */
/*                                                                            */
/*   Effets du facteur :                                                      */
/*   - factor > 1 : Agrandissement (zoom avant)                               */
/*     Exemple : 1.1 = agrandissement de 10%                                  */
/*   - factor < 1 : Réduction (zoom arrière)                                  */
/*     Exemple : 0.9 = réduction de 10%                                       */
/*   - factor = 1 : Aucun changement                                          */
/*                                                                            */
/*   Note : Cette fonction est typiquement appelée en réponse aux             */
/*   événements de la molette de la souris.                                   */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*   - factor : coefficient multiplicateur pour le zoom                       */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	zoom(t_app *app, float factor)
{
	if (app->matrix.zoom * factor < Z_DEFAULT)
	{
		app->matrix.zoom = Z_DEFAULT;
		return ;
	}
	else if (app->matrix.zoom * factor > Z_MAX)
	{
		app->matrix.zoom = Z_MAX;
		return ;
	}
	else
		app->matrix.zoom *= factor;
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}
