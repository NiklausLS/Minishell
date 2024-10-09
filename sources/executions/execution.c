/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 22:32:34 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_real_command(t_token *data, t_exec *ex, t_minishell *ms)
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
	ft_free_input_data(&ms->input);
	rl_clear_history();
	exit(127);
}

/*
 * Will execute the command after finding it's path
 */
void	execute_command(t_token *data, t_exec *ex, t_minishell *ms)
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
		make_builtin(data, ex);
		exit(0);
	}
	else
		execute_real_command(data, ex, ms);
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
	if (make_builtin(data, ex) == 1)
		return (1);
	dup2(old_in, STDIN_FILENO);
	dup2(old_out, STDOUT_FILENO);
	if (protected_close(old_in) == 1)
		return (1);
	if (protected_close(old_out) == 1)
		return (1);
	return (0);
}
