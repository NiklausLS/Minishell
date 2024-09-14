/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:46:11 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/30 18:55:27 by nileempo         ###   ########.fr       */
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
 * Copy stdin and stdout to make sure every command start with the original
 * Protect my code from eventual mean correctors
 */
int	exec_command(t_token *start, t_token *end, t_exec *ex)
{
	int	start_stdin;
	int	start_stdout;
	//printf("--- start of exec_command\n");
	start_stdin = dup(STDIN_FILENO);
	start_stdout = dup(STDOUT_FILENO);

	if (make_all_redirections(start, end) == 1)
		return (1);
	if (make_child(start, end, ex) != 0)
		return (1);
	dup2(start_stdin, STDIN_FILENO);
	dup2(start_stdout, STDOUT_FILENO);
	close(start_stdin);
	close(start_stdout); 
	//printf("--- end of exec_command\n");
	return (0);
}