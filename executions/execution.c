/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/27 22:53:22 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//for test because i'm a donkey
/*static void wait_for_child(pid_t pid)
{
    int status;

    printf("parent process waiting for child PID: %d\n", pid);
    waitpid(pid, &status, 0);
    printf("child process %d stop status = %d\n", 
           pid, WEXITSTATUS(status));
}*/

static t_token	*find_command(t_token *start, t_token *end)
{
	t_token	*cmd;

	cmd = start;
	while (cmd != end && cmd->type != COMMAND)
		cmd = cmd->next;
	return (cmd);
}

static t_token	*find_command_end(t_token *start)
{
	t_token	*cmd;

	cmd = start;
	while (cmd && cmd->next)
	{
		if (cmd->next->type == PIPE)
			return (cmd);
		if (cmd->next->type == COMMAND)
			return (cmd);
		cmd = cmd->next;
	}
	printf("- in find_command_end : cmd is %s\n", cmd->value);
	return (cmd);
}

static int	make_child(t_token *start, t_token *end, t_exec *ex)
{
	pid_t			pid;
	t_token	*cmd;

	pid = fork();
	printf("-- in make_child : start = %s end = %s\n", start->value, end->value);
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", 2);
		return (1);
	}
	else if (pid == 0)
	{
		setup_in_and_out(ex);
		if (make_all_redirections(start, end) == 1)
			return (1);
		cmd = find_command(start, end);
		if (get_builtin(start) == 0)
			make_builtin(start, ex);
		else
		{
			make_execve(cmd, ex);
		}
		return (0);
	}
	return (0);
}

int	make_execve(t_token *data, t_exec *ex)
{
	printf("--- in make_execve : cmd is %s\n", data->value);
	make_path(ex, data);
	printf("--- path is %s\n", data->path);
	if (!data->args)
		data->args = ft_split(data->value, ' ');
	if (execve(data->path, data->args, ex->env) == -1)
	{
		perror("execve failed");
		exit(127);
	}
	return (0);
}

int	exec_all(t_token *cmd, t_exec *ex)
{
	t_token	*current;
	t_token	*start;
	t_token	*end;

	current = cmd;
	start = cmd;
	printf("- in exec_all\n");
	ex->prev_pipe = STDIN_FILENO;
	while (current != NULL)
	{
		end = find_command_end(current);
		if (current->next && current->next->type == PIPE)
		{
			if (setup_pipes(ex) != 0)
				return (1);
		}
		if (current->type == COMMAND)
		{
			if (make_child(start, end, ex) != 0)
				return (1);
		}
		if (end && end->type == PIPE)
		{
			setup_pipe_end(ex);
			current = end->next;
		}
		else
		{
			if (end)
				current = end->next;
			else
				current = NULL;
		}
		start = current;
	}
	wait_for_children();
	return (0);
}
