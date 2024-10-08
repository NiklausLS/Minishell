/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/08 21:53:58 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	only_redirections(t_token **current);

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

static void	exec_commands(t_exec *ex, t_token **data, int *is_first_cmd)
{
	t_token	*current;
	int		built_in;

	current = *data;
	built_in = 0;
	// printf("IN EXEC_COMMAND\n");
	while (current && current->type != PIPE)
		current = current->next;
	built_in = get_builtin(*data);
	if (built_in == 0 && current == NULL)
		exec_builtin(*data, ex);
	else
	{
		if (current && current->type == PIPE)
		{
			if (protected_pipe(ex->pipefd) == -1)
				return ;
		}
		fork_and_exec(ex, *data, *is_first_cmd, current != NULL);
	}
	*is_first_cmd = 0;
	while (*data && (*data)->type != PIPE)
		*data = (*data)->next;
	if (*data && (*data)->type == PIPE)
		*data = (*data)->next;
}

static int	only_redirections(t_token **current)
{
	int	input;
	int	output;

	// printf("IN only redirection\n");
	input = -1;
	output = -1;
	while (*current && ((*current)->type == INPUT || (*current)->type == OUTPUT
			|| (*current)->type == HEREDOC || (*current)->type == APPEND))
	{
		if ((*current)->type == INPUT || (*current)->type == HEREDOC)
		{
			if (input != -1)
				protected_close(input);
			input = make_input(*current);
			if (input == -1)
				return (-1);
			printf("input fd = %d\n", input);
		}
		else if ((*current)->type == OUTPUT || (*current)->type == APPEND)
		{
			if (output != -1)
				protected_close(output);
			output = make_output(*current);
			printf("output fd = %d\n", output);
			if (output == -1)
				return (-1);
		}
		*current = (*current)->next;
	}
	// printf("END of only redirection\n");
	return (0);
}

int	execute_all_commands(t_token *data, t_exec *ex)
{
	t_token	*current;
	int		is_first_cmd;

	current = data;
	is_first_cmd = 1;
	while (current)
	{
		if (only_redirections(&current) == -1)
		{
			ex->last_status = 1;
			// printf("END only_redirectio status = %d\n", ex->last_status);
			return (1);
		}
		if (current && current->type == COMMAND)
			exec_commands(ex, &current, &is_first_cmd);
		else
			current = current->next;
	}
	ex->last_status = wait_child_process();
	// printf("END execute _all_commands\n");
	// printf("- lasft_atoit_status = %d\n",ex->last_status);
	return (0);
}
