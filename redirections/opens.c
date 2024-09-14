/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:15:59 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/14 17:14:29 by nileempo         ###   ########.fr       */
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

int open_output(t_token *data)
{
    int     fd;
    t_token *current;

    fd = -1;
    current = data;
    printf("Entering open_output\n");
    if (current->type == OUTPUT && current->next)
    {
        printf("Attempting to open file '%s' for output\n", current->next->value);
        fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("open failed");
            printf("Error opening file: %s\n", strerror(errno));
            print_error(1, current->next->value);
            current->exec_fail = 1;
        }
        else
        {
            printf("File opened successfully with fd=%d\n", fd);
        }
    }
    else if (current->type == APPEND && current->next)
    {
        printf("Attempting to open file '%s' for append\n", current->next->value);
        fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("open failed");
            printf("Error opening file: %s\n", strerror(errno));
            print_error(1, current->next->value);
            current->error = 1;
        }
        else
        {
            printf("File opened successfully with fd=%d\n", fd);
        }
    }
    printf("Exiting open_output with fd=%d\n", fd);
    return (fd);
}