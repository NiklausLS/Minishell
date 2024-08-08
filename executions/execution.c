/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/08/08 20:49:01 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Find the position of the next command
 */
t_token	*find_command(t_token *start, t_token *end)
{
	t_token	*cmd;

	cmd = start;
	while (cmd != end && cmd->type != COMMAND)
		cmd = cmd->next;
	return (cmd);
}

/*
 * find the position of the next command
 */
static t_token	*get_command_end(t_token *start)
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
	//printf("- in find_command_end : cmd is %s\n", cmd->value);
	return (cmd);
}

/*
 * Make a process for each node and use a function depending of the type of the token inside
 */
int	make_child(t_token *start, t_exec *ex)
{
	pid_t	pid;

	pid = fork();
	//printf("---- in make_child : start = %s end = %s\n",
	//	start->value, end->value);
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", 2);
		return (1);
	}
	else if (pid == 0)
	{
		setup_in_and_out(ex);
		if (get_builtin(start) == 0)
			make_builtin(start, ex);
		else
		{
			//printf("*** --- before make_execve\n");
			make_execve(start, ex);
			exit(127);
		}
		exit (0);
	}
	return (0);
}

/*
 * Will execute the command after finding it's path
 */
int	make_execve(t_token *data, t_exec *ex)
{
	//printf("--- in make_execve : cmd is %s\n", data->value);
	make_path(ex, data);
	//printf("--- path is %s\n", data->path);
	if (data->path == NULL)
	{
		print_error(1, data->value);
		exit (1);
	}
	if (!data->args)
		data->args = ft_split(data->value, ' ');
	if (execve(data->path, data->args, ex->env) == -1)
	{
		//print_error(1, data->value);
		exit(127);
	}
	return (0);
}

/*
 * Loot that will go throught every node
 */
int	exec_all(t_token *cmd, t_exec *ex)
{
	t_token	*current;
	t_token	*end;
	int	start_stdin;
	int	start_stdout;

	current = cmd;
	ex->prev_pipe = STDIN_FILENO;
	start_stdin = dup(STDIN_FILENO);
	start_stdout = dup(STDOUT_FILENO);
	while (current != NULL)
	{
		end = get_command_end(current);
		if (current->next && current->next->type == PIPE)
			if (setup_pipes(ex) != 0)
				return (1);
		if (make_all_redirections(current, end) == 1)
			return (1);
		if (current->type == COMMAND)
		{
			if (exec_command(current, end, ex) != 0)
				return (1);
		}
		dup2(start_stdin, STDIN_FILENO);
		dup2(start_stdout, STDOUT_FILENO);
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
	}
	close(start_stdin);
	close(start_stdout); 
	wait_for_children();
	return (0);
}
