/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:46:11 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/10 19:00:08 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to change
void	wait_for_children(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		/*if (WIFEXITED(status))
			printf("child %d : status %d\n",
				pid, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("child %d : stop signal %d\n",
				pid, WTERMSIG(status));*/
		pid = waitpid(-1, &status, 0);
	}
}
/*
 * get the next command and call make_child if there is one
 * 
 */
int	exec_command(t_token *start, t_token *end, t_exec *ex)
{
	t_token *cmd;

	cmd = find_command(start, end);
	if (cmd && cmd->type == COMMAND)
	{
		if (make_child(start, ex) != 0)
			return (1);
	}
	//printf("--- end of exec_command\n");
	return (0);
}

