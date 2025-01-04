/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:32:22 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/24 22:32:22 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'affichage des messages d'erreur sur la sortie d'erreur.       */
/*                                                                            */
/*   Cette fonction affiche des messages d'erreur spécifiques en fonction     */
/*   du code d'erreur reçu. Les messages sont envoyés sur la sortie           */
/*   d'erreur (fd 2) pour une gestion appropriée des erreurs.                 */
/*                                                                            */
/*   Messages d'erreur gérés :                                                */
/*   - ERR_ARGS : Arguments invalides fournis au programme                    */
/*   - ERR_MALLOC : Échec d'allocation mémoire                                */
/*   - ERR_DUP : Valeurs dupliquées détectées                                 */
/*   - DEBUG : Message de débogage personnalisé                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - error : code d'erreur entier déterminant le message à afficher         */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	print_error(int error)
{
	ft_putstr_fd("Error: ", 2);
	if (error == ERR_ARGS)
		ft_putstr_fd("Invalide arguments\n", 2);
	else if (error == ERR_MALLOC)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (error == ERR_DUP)
		ft_putstr_fd("Dup values\n", 2);
	else if (error == DEBUG)
		ft_putstr_fd("et ben faut bosser tes examens\n", 2);
}
