/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 17:24:27 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_command(t_token *data, t_exec *ex)
{
	t_token	*end;

	end = get_end(data);
	make_all_redirections(data, end);
	if (get_builtin(data) == 0)
		make_builtin(data, ex);
	else
	{
		parse_args(data);
		make_path(ex, data);
		print_node(data);
		execve(data->path, data->args, ex->env);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(data->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

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
