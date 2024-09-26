/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 17:29:25 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void handle_child_process(t_exec *ex, t_token *data, int is_first_cmd, int has_pipe)
{
    if (!is_first_cmd)
    {
        dup2(ex->prev_pipe, STDIN_FILENO);
        close(ex->prev_pipe);
    }

    if (has_pipe)
    {
        close(ex->pipefd[READ_END]);
        dup2(ex->pipefd[WRITE_END], STDOUT_FILENO);
        close(ex->pipefd[WRITE_END]);
    }
    execute_command(data, ex);
}

static void handle_parent_process(t_exec *ex, int is_first_cmd, int has_pipe)
{
    if (!is_first_cmd)
    {
        close(ex->prev_pipe);
    }

    if (has_pipe)
    {
        close(ex->pipefd[WRITE_END]);
        ex->prev_pipe = ex->pipefd[READ_END];
    }
    else
    {
        ex->prev_pipe = -1;
    }
}

static int handle_redirection_only(t_token *data)
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


void execute_all_commands(t_token *data, t_exec *ex)
{
    t_token *current = data;
    int is_first_cmd = 1;
	t_token *next_pipe;

    while (current)
    {
        if (current->type == INPUT || current->type == OUTPUT || current->type == HEREDOC || current->type == APPEND)
        {
            if (handle_redirection_only(current) == -1)
            {
                ft_putstr_fd("Redirection error\n", 2);
                return;
            }
            while (current && current->type != COMMAND && current->type != PIPE)
                current = current->next;
        }
        if (current->type == COMMAND)
        {
            next_pipe = current;
            if (!next_pipe)
				return;
            while (next_pipe && next_pipe->type != PIPE)
                next_pipe = next_pipe->next;
            if (next_pipe && next_pipe->type == PIPE)
            {
                if (pipe(ex->pipefd) == -1)
                {
                    perror("pipe");
                    return;
                }
            }
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return;
            }
            else if (pid == 0)
            {
                handle_child_process(ex, current, is_first_cmd, next_pipe != NULL);
                exit(EXIT_FAILURE);
            }
            else
            {
                handle_parent_process(ex, is_first_cmd, next_pipe != NULL);
            }
            is_first_cmd = 0;
            while (current && current->type != PIPE)
                current = current->next;
            if (current && current->type == PIPE)
                current = current->next;
        }
        else
            current = current->next;
    }
    while (wait(NULL) > 0);
}
