/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:40 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/09 20:59:23 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->args = NULL;
	new->path = NULL;
	new->input = NULL;
	new->output = NULL;
	new->heredoc_delim = NULL;
	new->error = -1;
	return (new);
}

void	add_token(t_input *input, t_token *new)
{
	t_token	*tmp;

	if (!input->tokens)
		input->tokens = new;
	else
	{
		tmp = input->tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
