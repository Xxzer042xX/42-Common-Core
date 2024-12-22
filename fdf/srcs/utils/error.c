/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:42:39 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/10 21:45:15 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère l'affichage standardisé des messages d'erreur        */
/*   du programme FdF sur la sortie d'erreur standard (stderr).               */
/*                                                                            */
/*   Messages d'erreur par code :                                             */
/*   1. ERR_ARGS :                                                            */
/*      - "Invalid arguments"                                                 */
/*      - Usage incorrect du programme ou arguments manquants                 */
/*                                                                            */
/*   2. ERR_MALLOC :                                                          */
/*      - "Memory allocation failed"                                          */
/*      - Échec d'allocation dynamique de mémoire                             */
/*                                                                            */
/*   3. ERR_FILE :                                                            */
/*      - "Cannot open file"                                                  */
/*      - Problèmes d'accès ou de lecture du fichier                          */
/*                                                                            */
/*   4. ERR_FORMAT :                                                          */
/*      - "Invalid file format"                                               */
/*      - Format de données incorrect dans le fichier                         */
/*                                                                            */
/*   5. ERR_MLX :                                                             */
/*      - "MLX initialisation failed"                                         */
/*      - Échec de l'initialisation graphique                                 */
/*                                                                            */
/*   Format de sortie :                                                       */
/*   - Préfixe "Error: " suivi du message spécifique                          */
/*   - Utilise ft_putstr_fd pour écrire sur stderr (fd 2)                     */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - error : code d'erreur défini dans les constantes                       */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Le code d'erreur reçu en paramètre                                     */
/*     Permet la propagation du code d'erreur dans le programme               */
/*                                                                            */
/* ************************************************************************** */
int	error_exit(int error)
{
	ft_putstr_fd("Error: ", 2);
	if (error == ERR_ARGS)
		ft_putstr_fd("Invalide arguments\n", 2);
	else if (error == ERR_MALLOC)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (error == ERR_FILE)
		ft_putstr_fd("Cannot open file\n", 2);
	else if (error == ERR_FORMAT)
		ft_putstr_fd("Invalide file format\n", 2);
	else if (error == ERR_MLX)
		ft_putstr_fd("MLX initialisation failed\n", 2);
	else if (error == DEBUG)
		ft_putstr_fd("et ben faut bosser tes examens\n", 2);
	return (error);
}
