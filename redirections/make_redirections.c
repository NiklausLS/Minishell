/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:17:53 by nileempo          #+#    #+#             */
/*   Updated: 2024/08/30 11:25:26 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * check if there is a input or an output and open it
 */
static int	redirections(t_token *current, int *last_input, int *last_output)
{
	if (current->type == INPUT || current->type == HEREDOC)
	{
		if (*last_input != -1)
			if (protected_close(*last_input) == 1)
				return (1);
		*last_input = open_input(current);
		if (*last_input == -1)
			return (1);
	}
	if (current->type == OUTPUT || current->type == APPEND)
	{
		if (*last_output != -1)
			if (protected_close(*last_output) == 1)
				return (1);
		*last_output = open_output(current->next);
		if (*last_output == -1)
			return (1);
	}
	return (0);
}

/*
 * dup the input and check if it worked
 */
static int	dup_input(int fd)
{
	//printf("IN dup input\n");
	//printf("fd = %d\n", fd);
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			//ft_putstr_fd("Minishell: dup2 stdin error\n", 2);
			close (fd);
			return (1);
		}
		close (fd);
	}
	return (0);
}

/*
 * dup the output and check if it's ok
 */
static int	dup_output(int fd)
{
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (1);
		}
		close (fd);
	}
	return (0);
}

/*
 * Check every node and open/close input and output accordingly
 */
int	make_all_redirections(t_token *start, t_token *end)
{
	t_token	*current;
	int		last_input;
	int		last_output;

	current = start;
	last_input = -1;
	last_output = -1;
	//printf("in make all redirections\n");
	while (current && current != end)
	{
		if (redirections(current, &last_input, &last_output) == 1)
			return (1);
		current = current->next;
	}
	//printf("before dup_input\n");
	if (dup_input(last_input) == 1)
		return (1);
	//printf("after dup_input\n");
	if (dup_output(last_output) == 1)
		return (1);
	return (0);
}
