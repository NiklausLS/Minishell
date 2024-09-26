/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 17:20:28 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Will execute the command after finding it's path
 */
int	make_execve(t_token *data, t_exec *ex)
{
	if (make_path(ex, data) == 1)
	{
		print_error(1, data->value);
		exit(127);
	}
	printf("-- in make_execve : cmd is %s\n", data->value);
	printf("--- path is %s\n", data->path);
	if (!data->args)
		parse_args(data);
	/*for (int i = 0; data->args[i] != NULL; i++)
	{
    	printf("data->args[%d] = %s\n", i, data->args[i]);
	}
	*/
	print_node(data);
	/*if (execve(data->path, data->args, ex->env) == -1)
	{
		perror("execve failed");
		exit(127);
	}*/
	return (0);
}
