/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:46:11 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/18 15:44:09 by nileempo         ###   ########.fr       */
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
		if (WIFEXITED(status))
			printf("child %d status is %d\n",
				pid, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("child %d stop by signal %d\n",
				pid, WTERMSIG(status));
		pid = waitpid(-1, &status, 0);
	}
}