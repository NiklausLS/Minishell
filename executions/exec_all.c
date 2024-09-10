/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:51:07 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/10 18:56:46 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_exec(int *start_stdin, int *start_stdout, t_exec *ex)
{
	ex->prev_pipe = STDIN_FILENO;
	*start_stdin = dup(STDIN_FILENO);
	*start_stdout = dup(STDOUT_FILENO);
}

static int	process_command(t_token *current, t_token *end, t_exec *ex)
{
	if (current->next && current->next->type == PIPE)
		if (setup_pipes(ex) != 0)
			return (1);
	if (make_all_redirections(current, end) == 1)
		return (1);
	if (current->type == COMMAND)
		if (exec_command(current, end, ex) != 0)
			return (1);
	return (0);
}

static void	restore_io(int start_stdin, int start_stdout)
{
	dup2(start_stdin, STDIN_FILENO);
	dup2(start_stdout, STDOUT_FILENO);
}

static t_token	*move_to_next(t_token *end, t_exec *ex)
{
	if (end && end->type == PIPE)
	{
		setup_pipe_end(ex);
		return (end->next);
	}
	if (end)
		return (end->next);
	return (NULL);
}

int	exec_all(t_token *cmd, t_exec *ex)
{
	t_token	*current;
	t_token	*end;
	int		start_stdin;
	int		start_stdout;

	current = cmd;
	init_exec(&start_stdin, &start_stdout, ex);
	while (current != NULL)
	{
		end = get_command_end(current);
		if (process_command(current, end, ex) != 0)
			break ;
		restore_io(start_stdin, start_stdout);
		current = move_to_next(end, ex);
	}
	close(start_stdin);
	close(start_stdout);
	wait_for_children();
	if (current != NULL)
		return (1);
	return (0);
}
