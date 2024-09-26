/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:15:59 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 23:56:10 by nileempo         ###   ########.fr       */
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
	if (current->type == INPUT && current->next)
	{
		fd = open(current->next->value, O_RDONLY, 0644);
		if (fd == -1)
		{
			print_error(0, current->next->value);
			return (-1);
		}
	}
	else if (current->type == HEREDOC && current->next)
		fd = make_heredoc(current->next->value);
	return (fd);
}

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
			print_error(1, current->next->value);
	}
	else if (current->type == APPEND && current->next)
	{
		fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(1, current->next->value);
			current->error = 1;
		}
	}
	return (fd);
}

int	handle_redirection_only(t_token *data)
{
	int	fd;

	fd = -1;
	while (data)
	{
		if (data->type == INPUT || data->type == OUTPUT
			|| data->type == HEREDOC || data->type == APPEND)
		{
			if (data->type == INPUT || data->type == HEREDOC)
				fd = open_input(data);
			else
				fd = open_output(data);
			if (fd == -1)
				return (-1);
		}
		data = data->next;
	}
	return (fd);
}
