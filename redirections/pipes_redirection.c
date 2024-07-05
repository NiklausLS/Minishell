/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:26:18 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 22:05:46 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void    make_pipe(t_commands *cmd, int *prev_pipe, int pipefd[2])
{
    if (*prev_pipe != -1)
    {
        dup2(*prev_pipe, STDIN_FILENO);
        close(*prev_pipe);
    }
    if (cmd->next && cmd->next->pipe_type == 1)
    {
        close(pipefd[READ_END]);
        dup2(pipefd[WRITE_END], STDOUT_FILENO);
        close(pipefd[WRITE_END]);
    }
}

void    close_pipe(t_commands *cmd, int *prev_pipe, int pipefd[2])
{
    if (*prev_pipe != -1)
        close(*prev_pipe);
	if (cmd->next && cmd->next->pipe_type == 1)
	{
		close(pipefd[WRITE_END]);
		*prev_pipe = pipefd[READ_END];
	}
	else
		*prev_pipe = -1;
}
