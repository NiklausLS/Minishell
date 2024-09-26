/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:15:59 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 17:08:03 by nileempo         ###   ########.fr       */
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
	//printf("in open input\n");
	if (current->type == INPUT && current->next)
	{
		fd = open(current->next->value, O_RDONLY, 0644);
		if (fd == -1)
		{
			print_error(0, current->next->value);
			//current->exec_fail = 1;
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

int open_output(t_token *data)
{
    int     fd;
    t_token *current;

    fd = -1;
    current = data;
    //printf("Entering open_output\n");
    if (current->type == OUTPUT && current->next)
    {
        //printf("START open file '%s' for output\n", current->next->value);
        fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            //perror("open failed");
            //printf("Error opening file: %s\n", strerror(errno));
            print_error(1, current->next->value);
            //current->exec_fail = 1;
        }
    }
    else if (current->type == APPEND && current->next)
    {
        //printf("START open file '%s' for append\n", current->next->value);
        fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            print_error(1, current->next->value);
            current->error = 1;
        }
    }
    //printf("END open_output with fd=%d\n", fd);
    return (fd);
}

int handle_redirection_only(t_token *data)
{
	int fd;

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
