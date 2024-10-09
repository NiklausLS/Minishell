/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:00:22 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 21:39:48 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_builtin(t_token *data)
{
	if (ft_strcmp(data->value, "env") == 0)
		return (0);
	else if (ft_strcmp(data->value, "echo") == 0)
		return (0);
	else if (ft_strcmp(data->value, "pwd") == 0)
		return (0);
	else if (ft_strcmp(data->value, "export") == 0)
		return (0);
	else if (ft_strcmp(data->value, "unset") == 0)
		return (0);
	else if (ft_strcmp(data->value, "cd") == 0)
		return (0);
	else if (ft_strcmp(data->value, "exit") == 0)
		return (0);
	return (1);
}

int	make_builtin(t_token *data, t_exec *ex)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(data->value, "cd") == 0)
		ret = make_cd(ex, data);
	if (ft_strcmp(data->value, "env") == 0)
		ret = make_env(ex->env);
	else if (ft_strcmp(data->value, "echo") == 0)
		ret = make_echo(data);
	else if (ft_strcmp(data->value, "pwd") == 0)
		ret = make_pwd();
	else if (ft_strcmp(data->value, "export") == 0)
		ret = make_export(data, ex);
	else if (ft_strcmp(data->value, "unset") == 0)
		ret = make_unset(data, ex);
	else if (ft_strcmp(data->value, "exit") == 0)
		make_exit(data, ex);
	return (ret);
}
