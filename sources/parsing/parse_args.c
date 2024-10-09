/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:57:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 20:58:29 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_node(t_token *node);

static int	count_text_nodes(t_token *current)
{
	int	count;

	count = 0;
	while (current && current->type == TEXT)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	copy_free_nodes(t_token *current, t_token *data, int arg_count)
{
	t_token	*next;
	int		i;

	i = 1;
	while (current && current->type == TEXT)
	{
		data->args[i] = ft_strdup(current->value);
		next = current->next;
		free_node(current);
		current = next;
		i++;
	}
	data->args[arg_count + 1] = NULL;
	data->next = current;
}

static void	free_node(t_token *node)
{
	if (node->args)
		free(node->args);
	if (node->path)
		free(node->path);
	if (node->value)
		free(node->value);
	free(node);
}

/*
 * Will go through every node until it found a pipe
 * everything who is not a redirection or a pipe will be given a argument type
 * @return : return 0 if everything is ok, 1 if a malloc failed
 */
int	parse_args(t_token *data)
{
	t_token	*current;
	int		arg_count;

	arg_count = count_text_nodes(data->next);
	data->args = malloc(sizeof(char *) * (arg_count + 2));
	if (!data->args)
		return (1);
	data->args[0] = ft_strdup(data->value);
	if (!data->args[0])
	{
		free(data->args);
		return (1);
	}
	current = data->next;
	copy_free_nodes(current, data, arg_count);
	return (0);
}
