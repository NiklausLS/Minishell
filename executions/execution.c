/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/30 20:37:03 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Find the position of the next command
 */
/*static t_token	*find_command(t_token *start, t_token *end)
{
	t_token	*cmd;

	cmd = start;
	while (cmd != end && cmd->type != COMMAND)
		cmd = cmd->next;
	return (cmd);
}*/

/*
 * find the position of the next command
 */
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
	//printf("- in find_command_end : cmd is %s\n", cmd->value);
	return (cmd);
}

/*
 * Make a process for each node and use a function depending of the type of the token inside
 */
int	make_child(t_token *start, t_token *end, t_exec *ex)
{
	pid_t	pid;

	pid = fork();
	printf("---- in make_child : start = %s end = %s\n",
		start->value, end->value);
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

	current = cmd;
	//printf("- in exec_all\n");
	ex->prev_pipe = STDIN_FILENO;
	while (current != NULL)
	{
		end = find_command_end(current);
		if (current->next && current->next->type == PIPE)
			if (setup_pipes(ex) != 0)
				return (1);
		if (current->type == COMMAND)
		{
			if (exec_command(current, end, ex) != 0)
				return (1);
		}
		if (end && end->type == PIPE)
		{
			setup_pipe_end(ex);
			current = end->next;
		}
		else
		{
			current = end;
			if (current)
				current = current->next;
		}
	}
	wait_for_children();
	return (0);
}
