/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/28 22:49:23 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_exec *ex, t_token *data, int f_cmd, int has_pipe)
{
	if (!f_cmd)
	{
		dup2(ex->prev_pipe, STDIN_FILENO);
		close(ex->prev_pipe);
	}
	if (has_pipe)
	{
		close(ex->pipefd[READ_END]);
		dup2(ex->pipefd[WRITE_END], STDOUT_FILENO);
		close(ex->pipefd[WRITE_END]);
	}
	execute_command(data, ex);
}

void	parent_process(t_exec *ex, int f_cmd, int has_pipe)
{
	if (!f_cmd)
		close(ex->prev_pipe);
	if (has_pipe)
	{
		close(ex->pipefd[WRITE_END]);
		ex->prev_pipe = ex->pipefd[READ_END];
	}
	else
		ex->prev_pipe = -1;
}

static void	exec_commands(t_exec *ex, t_token **current, int *is_first_cmd)
{
	t_token	*next_pipe;

	next_pipe = *current;
	while (next_pipe && next_pipe->type != PIPE)
		next_pipe = next_pipe->next;
	if (next_pipe && next_pipe->type == PIPE)
	{
		if (protected_pipe(ex->pipefd) == -1)
			return ;
	}
	fork_and_exec(ex, *current, *is_first_cmd, next_pipe != NULL);
	*is_first_cmd = 0;
	while (*current && (*current)->type != PIPE)
		*current = (*current)->next;
	if (*current && (*current)->type == PIPE)
		*current = (*current)->next;
}

static int	only_redirections(t_token **current)
{
	while (*current && ((*current)->type == INPUT || (*current)->type == OUTPUT
			|| (*current)->type == HEREDOC || (*current)->type == APPEND))
	{
		if (handle_redirection_only(*current) == -1)
		{
			ft_putstr_fd("Minishell: redirection error\n", 2);
			return (-1);
		}
		*current = (*current)->next;
	}
	return (0);
}

int	execute_all_commands(t_token *data, t_exec *ex)
{
	t_token	*current;
	int		is_first_cmd;
	int		last_status;

	current = data;
	is_first_cmd = 1;
	last_status = 0;
	while (current)
	{
		if (only_redirections(&current) == -1)
			return (1);
		if (current && current->type == COMMAND)
			exec_commands(ex, &current, &is_first_cmd);
		else
			current = current->next;
	}
	last_status = wait_child_process();
	return (last_status);
}
