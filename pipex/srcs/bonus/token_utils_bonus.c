/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:51:39 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/28 09:51:39 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

/* ************************************************************************** */
/*                                                                            */
/*   Description :                                                            */
/*   Cette fonction traduit certains caractères spéciaux en leur valeur ASCII.*/
/*   Elle permet de remplacer les caractères d'échappement dans une chaîne.   */
/*   Par exemple, elle convertit 'n' en '\n', 't' en '\t', etc.               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - c : caractère à traiter                                                */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Le caractère spécial correspondant, ou le caractère original s'il n'y  */
/*     a pas de correspondance.                                               */
/*                                                                            */
/* ************************************************************************** */
static char	get_special_char(char c)
{
	if (c == 'n')
		return ('\n');
	if (c == 't')
		return ('\t');
	if (c == 'a')
		return ('\a');
	if (c == 'b')
		return ('\b');
	if (c == 'r')
		return ('\r');
	if (c == 'v')
		return ('\v');
	if (c == 'f')
		return ('\f');
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction : handle_quotes                                                 */
/*                                                                            */
/*   Description :                                                            */
/*   Cette fonction gère les guillemets dans la commande.                     */
/* 	 Elle permet d'activer ou de désactiver l'état des guillemets,            */
/*   en fonction du type de guillemet rencontré (simples ou doubles).         */
/*   Elle est utilisée pour savoir quand un argument est en train d'être      */
/*   extrait, et pour gérer les guillemets imbriqués.                         */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd    : commande à analyser                                           */
/*   - i      : index actuel dans la commande                                 */
/*   - qtype  : type de guillemet actif (0 si aucun)                          */
/*   - escaped : état d'échappement, pour savoir si un caractère est échappé  */
/*                                                                            */
/*   Retourne :                                                               */
/*   - 1 si un guillemet a été trouvé et traité, 0 sinon.                     */
/*                                                                            */
/* ************************************************************************** */
int	handle_quotes(const char *cmd, int *i, int *qtype, int *escaped)
{
	if (!*escaped && ft_isquote(cmd[*i]) && (!*qtype || cmd[*i] == *qtype))
	{
		if (!*qtype)
			*qtype = cmd[*i];
		else
			*qtype = 0;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction : handle_escape                                                 */
/*                                                                            */
/*   Description :                                                            */
/*   Cette fonction vérifie si un caractère dans la commande 				  */
/*   doit être échappé. 													  */
/*   Elle gère spécifiquement l'anti-slash ('\\') et permet de passer 		  */
/*   au caractère suivant sans interpréter le caractère spécial               */
/*   qu'il pourrait introduire.                                               */
/*   Elle prend en compte le type de guillemet actif pour savoir              */
/*   si les échappements sont valides ou non.                                 */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd    : commande à analyser                                           */
/*   - i      : index actuel dans la commande                                 */
/*   - qtype  : type de guillemet actif (0 si aucun)                          */
/*                                                                            */
/*   Retourne :                                                               */
/*   - 1 si un caractère doit être échappé, 0 sinon.                          */
/*                                                                            */
/* ************************************************************************** */
int	handle_escape(const char *cmd, int *i, int qtype)
{
	if (qtype == '\'')
		return (0);
	if (cmd[*i] == '\\')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction : handle_esc_token                                              */
/*                                                                            */
/*   Description :                                                            */
/*   Cette fonction gère l'ajout d'un caractère échappé dans un token.        */
/*   Si un caractère échappé est rencontré, il est traité selon le type de    */
/*   guillemet actuel (simple ou double).                                     */
/*   Les caractères spéciaux sont transformés via la fonction                 */
/*   get_special_char.                                                        */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - token : token en cours d'extraction                                    */
/*   - cmd   : commande source                                                */
/*   - i     : index actuel dans la commande                                  */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Aucun retour, mais le token est modifié en place.                      */
/*                                                                            */
/* ************************************************************************** */
void	handle_esc_token(t_token *token, const char *cmd, int *i)
{
	if (token->qtype == '\'')
		token->str[token->index] = cmd[*i];
	else
		token->str[token->index] = get_special_char(cmd[*i]);
	token->index++;
}
