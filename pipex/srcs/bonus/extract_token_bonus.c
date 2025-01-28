/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:53:06 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/28 09:53:06 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static int	handle_specials(t_token *token, const char *cmd, int *i);

/* ************************************************************************** */
/*                                                                            */
/*   Extracteur d'arguments individuels d'une commande.                       */
/*                                                                            */
/*   Cette fonction isole un argument en :                                    */
/*   1. Allouant un buffer de 1024 caractères pour l'argument                 */
/*      - Taille fixe pour éviter les débordements                            */
/*      - Limite la taille maximum d'un argument                              */
/*                                                                            */
/*   2. Parcours caractère par caractère avec gestion spéciale :              */
/*      - Des espaces (délimiteurs hors guillemets)                           */
/*      - Des guillemets simples et doubles (via handle_quotes)               */
/*      - Des caractères échappés (via handle_escape)                         */
/*                                                                            */
/*   Exemples d'extraction :                                                  */
/*   Dans "echo 'Hello World'" :                                              */
/*   - Premier appel : extrait "echo"                                         */
/*   - Second appel  : extrait "Hello World"                                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : commande source                                                  */
/*   - i : position actuelle (mise à jour après extraction)                   */
/*   - qtype : type de guillemet actif                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - L'argument extrait (chaîne allouée)                                    */
/*   - NULL si échec d'allocation                                             */
/*                                                                            */
/* ************************************************************************** */
char	*extract_token(const char *cmd, int *i, int *qtype)
{
	t_token	token;

	token.str = malloc(sizeof(char) * 1024);
	if (!token.str)
		return (NULL);
	token.index = 0;
	token.qtype = *qtype;
	token.esc = 0;
	while (cmd[*i] && (cmd[*i] != ' ' || token.qtype || token.esc))
	{
		if (handle_specials(&token, cmd, i))
			continue ;
		if (token.esc)
			handle_esc_token(&token, cmd, i);
		else
			token.str[token.index++] = cmd[*i];
		token.esc = 0;
		(*i)++;
	}
	token.str[token.index] = '\0';
	*qtype = token.qtype;
	return (token.str);
}

/* ************************************************************************** */
/*                                                                            */
/*   Description :                                                            */
/*   Gère les caractères spéciaux lors de l'extraction d'un token :           */
/*   - Les caractères d'échappement (\)                                       */
/*   - Les guillemets (simples et doubles)                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - token  : Structure contenant l'état du token en cours                  */
/*   - cmd    : Chaîne de commande source                                     */
/*   - i      : Pointeur sur l'index de position dans la commande             */
/*                                                                            */
/*   Retour :                                                                 */
/*    1 si un caractère spécial a été traité, 0 sinon                         */
/*                                                                            */
/*   Notes :                                                                  */
/*   - Utilise handle_escape et handle_quotes pour le traitement              */
/*   - Met à jour les états d'échappement et de guillemets dans token         */
/*                                                                            */
/* ************************************************************************** */
static int	handle_specials(t_token *token, const char *cmd, int *i)
{
	if (!token->esc && handle_escape(cmd, i, token->qtype))
	{
		token->esc = 1;
		return (1);
	}
	if (!token->esc && handle_quotes(cmd, i, &token->qtype, &token->esc))
	{
		(*i)++;
		return (1);
	}
	return (0);
}
