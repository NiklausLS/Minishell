/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 08:22:55 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_real_command(t_token *data, t_exec *ex)
{
	parse_args(data);
	make_path(ex, data);
	if (data->path != NULL)
		execve(data->path, data->args, ex->env);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(data->value, 2);
	ft_putstr_fd(": command not found\n", 2);
	ex->last_status = 127;
	free_array(data->args);
	free_exec_structure(ex);
	ft_free_input_data(ex->input);
	rl_clear_history();
	exit(127);
}

/*
 * Will execute the command after finding it's path
 */
void	execute_command(t_token *data, t_exec *ex)
{
	t_token	*end;

	end = get_end(data);
	if (make_all_redirections(data, end) == 1)
	{
		ex->last_status = 1;
		return ;
	}
	if (get_builtin(data) == 0)
	{
		ex->last_status = make_builtin(data, ex);
		exit(ex->last_status);
	}
	else
		execute_real_command(data, ex);
}

/*
 * exec builtin command without make child process
 */
int	exec_builtin(t_token *data, t_exec *ex)
{
	int	old_in;
	int	old_out;

	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);
	if (make_all_redirections(data, get_end(data)) == 1)
		return (1);
	ex->last_status = make_builtin(data, ex);
	if (ex->last_status != 0)
		return (ex->last_status);
	dup2(old_in, STDIN_FILENO);
	dup2(old_out, STDOUT_FILENO);
	if (protected_close(old_in) == 1)
		return (1);
	if (protected_close(old_out) == 1)
		return (1);
	return (0);
}

t_token	*get_end(t_token *start)
{
	t_token	*current;

	current = start;
	while (current != NULL && current->type != PIPE && current->next)
		current = current->next;
	return (current);
}
