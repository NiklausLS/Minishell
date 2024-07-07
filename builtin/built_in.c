/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:00:22 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/06 23:15:34 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list
//CD

int get_builtin(t_data *data, char **argv, t_exec *ex)
{
	if (ft_strcmp(data->cmd_lst->cmd, "cd") == 0)
	{
		printf("CD USED\n");
		make_cd(&argv[1]);
	}
    if (ft_strcmp(data->cmd_lst->cmd, "env") == 0)
	{
		printf("ENV USED\n");
		make_env(ex->env);
        return (0);
	}
	else if (ft_strcmp(data->cmd_lst->cmd, "exit") == 0)
	{
		printf("EXIT USED\n");
		make_exit();
	}
/*	else if (ft_strcmp(data->cmd, "echo") == 0)
    {
        printf("ECHO USED\n");
    }
    else if (ft_strcmp(data->cmd, "pwd") == 0)
    {
        printf("PWD USED\n");
    }
    else if (ft_strcmp(data->cmd, "export") == 0)
    {
        printf("EXPORT USED\n");
    }
    else if (ft_strcmp(data->cmd, "unset") == 0)
    {
        printf("UNSET USED\n");
    }*/
    return (-1);
}
