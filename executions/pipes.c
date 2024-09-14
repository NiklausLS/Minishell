/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/13 19:07:59 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_pipes(t_exec *ex)
{
	if (pipe(ex->pipefd) == -1)
	{
		ft_putstr_fd("Minishell: pipe error\n", 2);
		return (1);
	}
	return (0);
}

int	setup_in_and_out(t_exec *ex)
{
	if (ex->prev_pipe != STDIN_FILENO)
	{
		dup2(ex->prev_pipe, STDIN_FILENO);
		close(ex->prev_pipe);
	}
	if (ex->pipefd[1] != STDOUT_FILENO)
	{
		dup2(ex->pipefd[1], STDOUT_FILENO);
		close(ex->pipefd[1]);
	}
	return (0);
}

void	setup_pipe_end(t_exec *ex)
{
	close(ex->pipefd[1]);
	if (ex->prev_pipe != STDIN_FILENO)
		close(ex->prev_pipe);
	ex->prev_pipe = ex->pipefd[0];
}

/*static void close_pipe(int pipefd[2])
{
    close(pipefd[0]);
    close(pipefd[1]);
}*/
