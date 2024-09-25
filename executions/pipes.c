/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 00:45:58 by nileempo         ###   ########.fr       */
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
		make_path(ex, data);
		parse_args(data);
		execve(data->path, data->args, ex->env);
		ft_putstr_fd("Minishell: command not found\n", 2);
		exit(127);
	}
}

static void	handle_child_process(t_exec *ex, t_token *data)
{
	if (ex->prev_pipe != -1)
	{
		dup2(ex->prev_pipe, STDIN_FILENO);
		close(ex->prev_pipe);
	}
	if (data->next != NULL && data->next->type == PIPE)
	{
		close(ex->pipefd[READ_END]);
		dup2(ex->pipefd[WRITE_END], STDOUT_FILENO);
		close(ex->pipefd[WRITE_END]);
	}
	else
	{
		close(ex->pipefd[READ_END]);
		close(ex->pipefd[WRITE_END]);
	}
	execute_command(data, ex);
}

static void	handle_parent_process(t_exec *ex, t_token *data, pid_t pid)
{
	if (ex->prev_pipe != -1)
		close(ex->prev_pipe);
	if (data->next != NULL && data->next->type == PIPE)
	{
		close(ex->pipefd[WRITE_END]);
		ex->prev_pipe = ex->pipefd[READ_END];
	}
	else
	{
		close(ex->pipefd[READ_END]);
		close(ex->pipefd[WRITE_END]);
		waitpid(pid, NULL, 0);
		ex->prev_pipe = -1;
	}
}

static void	execute_command_node(t_token *data, t_exec *ex)
{
	pid_t	pid;

	if (pipe(ex->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(ex, data);
	else
		handle_parent_process(ex, data, pid);
}

void	execute_all_commands(t_token *data, t_exec *ex)
{
	ex->prev_pipe = -1;
	//printf("EXECUTE ALL COMMANDS : data type = %d\n", data->type);
	//printf("check_if_cmd = %d\n", cmd_ok);
	if (check_if_cmd(data) == 1)
	{
		while (data != NULL)
		{
			if (data->type == COMMAND)
				execute_command_node(data, ex);
			data = data->next;
		}
	}
	if (data->type == OUTPUT || data->type == INPUT
		|| data->type == HEREDOC || data->type == APPEND)
	{
		if (make_all_redirections(data, get_end(data)) != 0)
			return ;
	}
	fprintf(stderr, "END execute all commands\n");
}
