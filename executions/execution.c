/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/13 18:50:45 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void wait_for_child(pid_t pid)
{
    int status;

    printf("Parent process waiting for child PID: %d\n", pid);
    waitpid(pid, &status, 0);
    printf("Child process (PID: %d) finished with status: %d\n", 
           pid, WEXITSTATUS(status));
}*/

static t_input_data	*find_command(t_input_data *start, t_input_data *end)
{
	t_input_data	*cmd;

	cmd = start;
	while (cmd != end && cmd->cmd_type != 1)
		cmd = cmd->next;
	return (cmd);
}

static t_input_data	*find_command_end(t_input_data *start)
{
	t_input_data	*cmd;

	cmd = start;
	while (cmd && cmd->next)
	{
		if (cmd->next->pipe_type == 1)
			return (cmd);
		if (cmd->next->cmd_type == 1)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

static int	make_child(t_input_data *start, t_input_data *end, t_exec *ex)
{
	pid_t			pid;
	t_input_data	*cmd;

	pid = fork();
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
		//if (cmd == end)
		//	return (0);
		exec_command(cmd, ex);
		return (1);
	}
	return (0);
}

int	exec_command(t_input_data *data, t_exec *ex)
{
	if (data->cmd_type != 1 || data->exec_fail != -1)
		return (0);
	make_path(ex, data);
	if (!data->args)
		data->args = ft_split(data->data, ' ');
	if (execve(data->path, data->args, ex->env) == -1)
	{
		perror("execve failed");
		exit(127);
	}
	return (0);
}

int	exec_all(t_input_data *cmd, t_exec *ex)
{
	t_input_data	*current;
	t_input_data	*start;
	t_input_data	*end;

	current = cmd;
	start = cmd;
	ex->prev_pipe = STDIN_FILENO;
	while (current != NULL)
	{
		end = find_command_end(current);
		if (current->next && current->next->pipe_type == 1)
		{
			if (setup_pipes(ex) != 0)
				return (1);
		}
		if (make_child(start, end, ex) != 0)
			return (1);
		if (end && end->pipe_type == 1)
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
