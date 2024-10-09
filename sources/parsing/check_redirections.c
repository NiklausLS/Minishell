/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:53:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 22:52:30 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * PARSING : Check the last node and returns an error
 * if it's a redirection 
 */
int	check_last_node(t_token *data)
{
	t_token	*current;

	if (data == NULL)
		return (0);
	current = data;
	while (current && current->next != NULL)
		current = current->next;
	if (!ft_strcmp(current->value, "<") || !ft_strcmp(current->value, "<<")
		|| !ft_strcmp(current->value, ">") || !ft_strcmp(current->value, ">>"))
	{
		ft_putstr_fd("Minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

static void	check_first_command(t_token *data)
{
	if (data->type != INPUT && data->type != HEREDOC
		&& data->type != OUTPUT && data->type != APPEND
		&& data->type != PIPE)
		data->type = COMMAND;
}

static int	check_if_file(t_token *current)
{
	if (current->type == PIPE && current->next)
	{
		if (current->next->type == PIPE)
		{
			ft_putstr_fd("Minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token `|'\n", 2);
			return (1);
		}
	}
	else if ((current->type == INPUT || current->type == HEREDOC
			|| current->type == OUTPUT || current->type == APPEND)
		&& current->next)
	{
		if (current->next->type == PIPE)
		{
			ft_putstr_fd("Minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token `|'\n", 2);
			return (1);
		}
		else
			current->next->type = FI;
	}
	return (0);
}

static int	check_attached_pipe(t_token *data)
{
	t_token	*current;
	int		i;

	if (data == NULL || data->value == NULL)
		return (0);
	current = data;
	i = ft_strlen(current->value);
	if (current->value[0] == '|')
	{
		if (i >= 1 && current->value[1] == '|')
		{
			ft_putstr_fd("Minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token `||'\n", 2);
			return (1);
		}
	}
	return (0);
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
		if (check_if_file(current) == 1 || check_attached_pipe(current) == 1)
			return (1);
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
