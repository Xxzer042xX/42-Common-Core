/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_z_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 06:37:09 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/11 06:38:46 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction analyse et extrait les données (hauteur Z et couleur)     */
/*   d'un point de la carte au format "z[,0xCOLOR]".                          */
/*                                                                            */
/*   Processus de parsing :                                                   */
/*   1. Validation du format Z :                                              */
/*      - Gère le signe négatif optionnel                                     */
/*      - Vérifie que les caractères suivants sont des chiffres               */
/*                                                                            */
/*   2. Extraction de la hauteur :                                            */
/*      - Convertit la chaîne en entier avec ft_atoi                          */
/*      - Stocke la valeur dans points[num_line][col].pos.z                   */
/*                                                                            */
/*   3. Traitement de la couleur (si présente) :                              */
/*      - Vérifie la présence du séparateur ','                               */
/*      - Valide le format hexadécimal avec ft_ishexa                         */
/*      - Convertit la couleur avec ft_atoi_base(hex_color, 16)               */
/*      - Si pas de couleur spécifiée : utilise COLOR_GRID                    */
/*                                                                            */
/*   Format attendu :                                                         */
/*   - "z" : nombre entier (avec signe optionnel)                             */
/*   - ",0xCOLOR" : partie optionnelle, COLOR en hexadécimal                  */
/*   Exemples : "5", "-3", "10,0xFF0000", "-2,0x00FF00"                       */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - z_value : chaîne à parser                                              */
/*   - num_line : index de la ligne dans la carte                             */
/*   - col : index de la colonne dans la ligne                                */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si le parsing réussit                                          */
/*   - ERR_FORMAT si :                                                        */
/*     * Format de nombre invalide                                            */
/*     * Format hexadécimal invalide                                          */
/*     * Caractères inattendus                                                */
/*                                                                            */
/* ************************************************************************** */
int	parsing_z(t_app *app, char *z_value, int num_line, int col)
{
	int		i;
	char	*hex_color;

	i = 0;
	if (z_value[i] == '-')
		i++;
	while (ft_isdigit(z_value[i]))
		i++;
	if (!z_value[i] || z_value[i] == ',')
	{
		app->map.points[num_line][col].pos.z = ft_atoi(z_value);
		if (z_value[i] == ',')
		{
			hex_color = &z_value[++i];
			if (!ft_ishexa(hex_color))
				return (ERR_FORMAT);
			app->map.points[num_line][col].color.ref = \
			ft_atoi_base(hex_color, 16);
			app->map.points[num_line][col].color.is_parsed = 1;
		}
		else
			app->map.points[num_line][col].color.ref = PURPLE;
		return (SUCCESS);
	}
	return (ERR_FORMAT);
}
