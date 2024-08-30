/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:15:59 by nileempo          #+#    #+#             */
/*   Updated: 2024/08/30 11:27:08 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Open if there is an input
 */
int	open_input(t_token *data)
{
	int		fd;
	t_token	*current;

	fd = -1;
	current = data;
	printf("in open input\n");
	if (current->type == INPUT && current->next)
	{
		fd = open(current->next->value, O_RDONLY, 0644);
		if (fd == -1)
		{
			print_error(0, current->next->value);
			current->exec_fail = 1;
			return (-1);
		}
	}
	else if (current->type == HEREDOC && current->next)
	{
		//printf("current = %s\n", current->next->value);
		fd = make_heredoc(current->next->value);
		//printf("fd heredoc = %d\n", fd);
	}
	return (fd);
}

/*
 * open if there is an output
 */
int	open_output(t_token *data)
{
	int		fd;
	t_token	*current;

	fd = -1;
	current = data;
	if (current->type == OUTPUT && current->next)
	{
		fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error(1, current->next->value);
			current->exec_fail = 1;
			//current->error = 1;
		}
	}
	else if (current->type == APPEND && current->next)
	{
		fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(1, current->next->value);
			//current->exec_fail = 1;
			current->error = 1;
		}
	}
	return (fd);
}
