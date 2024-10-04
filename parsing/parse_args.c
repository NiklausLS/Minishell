/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:57:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/03 20:19:21 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Will go through every node until it found a pipe
 * everything who is not a redirection or a pipe will be given a argument type
 * @return : return 0 if everything is ok, 1 if a malloc failed
 */
int	parse_args(t_token *data)
{
	t_token	*current;
	int		arg_count;

	printf("IN PARSE_ARGS\n");
	arg_count = count_text_nodes(data->next);
	data->args = malloc(sizeof(char *) * (arg_count + 2));
	if (!data->args)
		return (1);
	data->args[0] = ft_strdup(data->value);
	if (!data->args[0])
		return (1);
	current = data->next;
	copy_and_free_nodes(current, data, arg_count);
	return (0);
}

int	count_text_nodes(t_token *current)
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

void	copy_and_free_nodes(t_token *current, t_token *data, int arg_count)
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

void	free_node(t_token *node)
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
 * Will make the first node a command
 * check the rest to give them a type specific to each of them
 * redirection / pipe / argument / command
 * @return 0 if everything is ok, 1 if something is wrong
 * */
int	check_lst(t_token *data)
{
	t_token	*current;
	int		first_cmd;

	current = data;
	first_cmd = 1;
	while (current != NULL)
	{
		if (first_cmd == 1)
		{
			if (current->type != INPUT && current->type != HEREDOC
				&& current->type != OUTPUT && current->type != APPEND)
			{
				current->type = COMMAND;
				first_cmd = 0;
			}
			first_cmd = 0;
		}
		if ((current->type == INPUT || current->type == HEREDOC
				|| current->type == OUTPUT || current->type == APPEND)
			&& current->next)
			current->next->type = FI;
		if (current->type == PIPE && current->next)
		{
			if (current->next->type != INPUT && current->next->type != HEREDOC
				&& current->next->type != OUTPUT
				&& current->next->type != APPEND)
				current->next->type = COMMAND;
		}
		current = current->next;
	}
	return (0);
}
