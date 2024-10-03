/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/03 14:32:01 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Will execute the command after finding it's path
 */
void	execute_command(t_token *data, t_exec *ex)
{
	t_token	*end;

	printf("execute_command data->value = %s\n", data->value);
	end = get_end(data);
	//parse_args(data);
	make_all_redirections(data, end);
	//if (get_builtin(data) == 0)
	//	make_builtin(data, ex);
	//else
	//{
		parse_args(data);
		make_path(ex, data);
		printf("path = %s\n", data->path);
		for (int i = 0; data->args[i] != NULL; i++)
		{
    		printf("arg[%d] = %s\n", i, data->args[i]);
		}
		execve(data->path, data->args, ex->env);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(data->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	//}
}

/*
 * exec builtin command without make child process
 */
int	exec_builtin(t_token *data, t_exec *ex)
{
	int	old_in;
	int	old_out;

	printf("IN EXEC_BUILTIN\n");
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
	printf("END OF EXEC_BUILTIN\n");
	return (0);	
}
