/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/28 17:15:01 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Will execute the command after finding it's path
 */
void	execute_command(t_token *data, t_exec *ex)
{
	t_token	*end;

	end = get_end(data);
	make_all_redirections(data, end);
	if (get_builtin(data) == 0)
		make_builtin(data, ex);
	else
	{
		parse_args(data);
		make_path(ex, data);
		execve(data->path, data->args, ex->env);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(data->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

