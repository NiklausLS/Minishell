/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:00:22 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/12 20:08:02 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to do list
//CD

int get_builtin(t_token *data)
{
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
    printf("IN MAKE BUILTIN\n");
    //print_env(ex);
	if (ft_strcmp(data->value, "cd") == 0)
	{
		if (make_cd(ex, data) == 0)
            return (0);
    }
    if (ft_strcmp(data->value, "env") == 0)
	{
		if (make_env(ex->env) == 0)
            return (0);
	}
	else if (ft_strcmp(data->value, "exit") == 0)
		make_exit();
    else if (ft_strcmp(data->value, "echo") == 0)
        make_echo(data);
    else if (ft_strcmp(data->value, "pwd") == 0)
    {
        if (make_pwd() == 0)
            return (0);
    }
    else if (ft_strcmp(data->value, "export") == 0)
    {
        if (make_export(data, ex) == 0)
        {
            print_env(ex);
            return (0);
        }
    }
    else if (ft_strcmp(data->value, "unset") == 0)
    {
        make_unset(data, ex);
        return (0);
    }
    //print_env(ex);
    return (1);
}
