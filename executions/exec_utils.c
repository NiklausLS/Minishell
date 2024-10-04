/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:46:11 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/04 15:16:16 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int		status;

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
	{
		parent_process(ex, is_first_cmd, has_pipe);
		waitpid(pid, &status, 0);
	}
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
	}
	return (last_status);
}
