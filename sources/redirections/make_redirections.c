/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:17:53 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 00:27:15 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	make_input(t_token *current, int *last_input)
{
	if (current->type == INPUT || current->type == HEREDOC)
	{
		if (*last_input != -1)
		{
			if (protected_close(*last_input) == 1)
				return (1);
		}
		if (current->type == HEREDOC)
			*last_input = make_heredoc(current->next->value);
		else
			*last_input = open_input(current);
		if (*last_input == -1)
			return (1);
		if (dup2(*last_input, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 for stdin failed\n", 2);
			return (1);
		}
		close(*last_input);
		*last_input = -1;
	}
	return (0);
}

static int	make_open_output(t_token *current, int *last_output)
{
	if (current->type == OUTPUT)
		*last_output = open(current->next->value, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (current->type == APPEND)
		*last_output = open(current->next->value, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (*last_output == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}

static int	make_output(t_token *current, int *last_output)
{
	if (current->type == OUTPUT || current->type == APPEND)
	{
		if (*last_output != -1)
		{
			if (protected_close(*last_output) == 1)
				return (1);
		}
		if (make_open_output(current, last_output) == 1)
			return (1);
		if (dup2(*last_output, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 for stdout failed", 2);
			return (1);
		}
		close(*last_output);
		*last_output = -1;
	}
	return (0);
}

static int	redirections(t_token *current, int *last_input, int *last_output)
{
	if (make_input(current, last_input) == 1)
		return (1);
	if (make_output(current, last_output) == 1)
		return (1);
	return (0);
}

int	make_all_redirections(t_token *start, t_token *end)
{
	t_token	*current;
	int		last_input;
	int		last_output;

	current = start;
	last_input = -1;
	last_output = -1;
	while (current && current != end)
	{
		if (redirections(current, &last_input, &last_output) == 1)
		{
			current->error = 1;
			return (1);
		}
		current = current->next;
	}
	if (make_dup_and_close(last_input, last_output) == 1)
		return (1);
	return (0);
}
