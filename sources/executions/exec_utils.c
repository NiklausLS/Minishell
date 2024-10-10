/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:46:11 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 08:25:42 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_cmd(t_token *data)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (current->type == COMMAND)
			return (1);
		current = current->next;
	}
	return (0);
}

int	fork_and_exec(t_exec *ex, t_token *current, int is_first_cmd, int has_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork failed\n", 2);
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_process(ex, current, is_first_cmd, has_pipe);
	}
	else
		parent_process(ex, is_first_cmd, has_pipe);
	return (0);
}

int	wait_child_process(void)
{
	int	last_status;
	int	new_status;

	last_status = 0;
	while (wait(&new_status) > 0)
	{
		if (WIFEXITED(new_status))
			last_status = WEXITSTATUS(new_status);
		else if (WIFSIGNALED(new_status))
		{
			last_status = 128 + WTERMSIG(new_status);
			if (last_status == 130)
				ft_putchar_fd('\n', 1);
		}
	}
	return (last_status);
}

int	check_path(t_token *data, char **paths)
{
	char	*cmd_path;

	cmd_path = get_command(paths, data->value);
	if (cmd_path)
	{
		free(data->path);
		data->path = cmd_path;
		free_array(paths);
		return (0);
	}
	else if (access(data->value, F_OK | X_OK) == 0)
	{
		free(data->path);
		data->path = ft_strdup(data->value);
		free_array(paths);
		return (0);
	}
	return (1);
}

void	free_path(t_token *data)
{
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
}
