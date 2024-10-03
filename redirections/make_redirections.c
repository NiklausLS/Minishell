/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:17:53 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/30 21:46:14 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dup_output(int fd);
static int	dup_input(int fd);

/*
 * check if there is a input or an output and open it
 */
static int	redirections(t_token *current, int *last_input, int *last_output)
{
	if (current->type == INPUT || current->type == HEREDOC)
	{
		if (*last_input != -1)
		{
			printf("close last_input fd = %d\n", *last_input);
			if (protected_close(*last_input) == 1)
				return (1);
		}
		if (current->type == HEREDOC)
		{
			printf("--- IN heredoc\n");
			*last_input = make_heredoc(current->next->value);
		}
		else
		{
			printf("--- IN input redirection\n");
			*last_input = open_input(current);
		}
		if (*last_input == -1)
		{
			ft_putstr_fd("Minishell: could not open\n", 2);
			return (1);
		}
		printf("last_input fd = %d\n", *last_input);
		if (dup2(*last_input, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 for stdin failed\n", 2);
			return (1);
		}
		close(*last_input);
		*last_input = -1;
	}
	if (current->type == OUTPUT || current->type == APPEND)
	{
		if (*last_output != -1)
		{
			printf("CLOSE last_output fd = %d\n", *last_output);
			if (protected_close(*last_output) == 1)
				return (1);
		}
		if (current->type == OUTPUT)
		{
			printf("--- IN output redirection\n");
			*last_output = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (current->type == APPEND)
		{
			printf("--- IN append redirection\n");
			*last_output = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (*last_output == -1)
		{
			ft_putstr_fd("Minishell: open output failed\n", 2);
			return (1);
		}
		printf("last_output fd = %d\n", *last_output);
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
			return (1);
		current = current->next;
	}
	printf("last_input = %d\n", last_input);
	printf("last_output = %d\n", last_output);
	if (last_input == -1 && last_output == -1)
		return (0);
	if (dup_input(last_input) == 1)
		return (1);
	if (dup_output(last_output) == 1)
		return (1);
	if (last_input != -1)
		close (last_input);
	if (last_output != -1)
		close (last_output);
	return (0);
}

static int	dup_input(int fd)
{
	if (fd != -1)
	{
		printf("DUP_INPUT\n");
		printf("fd = %d\n", fd);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 input error\n", 2);
			protected_close(fd);
			return (1);
		}
		printf("input redirect OK\n");
		protected_close(fd);
	}
	return (0);
}

static int	dup_output(int fd)
{
	if (fd != -1)
	{
		printf("DUP_OUTPUT\n");
		printf("fd = %d\n", fd);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 output error\n", 2);
			protected_close(fd);
			return (1);
		}
		printf("output redirect OK\n");
		protected_close(fd);
	}
	return (0);
}

t_token	*get_end(t_token *start)
{
	t_token	*current;

	current = start;
	while (current != NULL && current->type != PIPE && current->next)
		current = current->next;
	return (current);
}
