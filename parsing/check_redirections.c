/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:53:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/04 15:35:21 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * PARSING : Check the last node and returns an error
 * if it's a redirection 
 */
int	check_last_node(t_token *data)
{
	t_token	*current;

	current = data;
	while (current && current->next != NULL)
	{
		printf("current = %s\n", current->value);
		current = current->next;
	}
	printf("current = %s\n", current->value);
	if (!ft_strcmp(current->value, "<") || !ft_strcmp(current->value, "<<")
		|| !ft_strcmp(current->value, ">") || !ft_strcmp(current->value, ">>"))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

static void	check_first_command(t_token *data)
{
	if (data->type != INPUT && data->type != HEREDOC
		&& data->type != OUTPUT && data->type != APPEND)
		data->type = COMMAND;
}

static void	check_if_file(t_token *current)
{
	if ((current->type == INPUT || current->type == HEREDOC
				|| current->type == OUTPUT || current->type == APPEND)
			&& current->next)
		current->next->type = FI;
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
			check_first_command(current);
			first_cmd = 0;
		}
		check_if_file(current);
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
