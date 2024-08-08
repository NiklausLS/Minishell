/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:00:22 by nileempo          #+#    #+#             */
/*   Updated: 2024/08/08 10:47:02 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to do list
//CD

int get_builtin(t_token *data)
{
	/*if (ft_strcmp(data->cmd_lst->cmd, "cd") == 0)
	{
        return (0);
	}*/
    //printf("*** IN GET BUILTIN\n");
    if (ft_strcmp(data->value, "env") == 0)
        return (0);
	else if (ft_strcmp(data->value, "exit") == 0)
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
    return (1);
}

int make_builtin(t_token *data, t_exec *ex)
{
	if (ft_strcmp(data->value, "cd") == 0)
	{
		printf("CD USED\n");
		if (make_cd(ex, data) == 0)
            return (0);
    }
    if (ft_strcmp(data->value, "env") == 0)
	{
		printf("ENV USED\n");
		if (make_env(ex->env) == 0)
            return (0);
        return (1);
	}
	else if (ft_strcmp(data->value, "exit") == 0)
	{
		printf("--- EXIT USED ---\n");
		make_exit();
	}
    else if (ft_strcmp(data->value, "echo") == 0)
    {
        printf("ECHO USED\n");
        make_echo(data);
    }
    else if (ft_strcmp(data->value, "pwd") == 0)
    {
        printf("--- PWD USED ---\n");
        if (make_pwd() == 0)
            return (0);
    }
    else if (ft_strcmp(data->value, "export") == 0)
    {
        printf("--- EXPORT USED ---\n");
        make_export(data, ex);
        return (0);
    }
    else if (ft_strcmp(data->value, "unset") == 0)
    {
        printf("UNSET USED\n");
        make_unset(data, ex);
        return (0);
    }
    return (1);
}
