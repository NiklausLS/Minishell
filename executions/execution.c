/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/30 17:28:25 by nileempo         ###   ########.fr       */
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
	make_all_redirections(data, end);
	if (get_builtin(data) == 0)
		make_builtin(data, ex);
	else
	{
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
	}
}

