/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:15:16 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/13 19:15:18 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_builtin(t_input_data *data, t_exec *ex)
//int get_builtin(t_data *data, char **argv, t_exec *ex)
{
	/*if (ft_strcmp(data->cmd_lst->cmd, "cd") == 0)
	{
		printf("CD USED\n");
		make_cd(&argv[1]);
	}*/
    if (ft_strcmp(data->data, "env") == 0)
	{
		printf("ENV USED\n");
		if (make_env(ex->env) == 1)
            return (1);
        return (0);
	}
	else if (ft_strcmp(data->data, "exit") == 0)
	{
		printf("--- EXIT USED ---\n");
		if (make_exit() == 1)
            return (1);
        return (2);//return sans erreur mais avec exit donc verifier la valeur de exit avec $?
	}
    /*else if (ft_strcmp(cmd->data, "echo") == 0)
    {
        printf("ECHO USED\n");
    }
    else if (ft_strcmp(data->cmd, "pwd") == 0)
    {
        printf("PWD USED\n");
    }*/
    else if (ft_strcmp(data->data, "export") == 0)
    {
        printf("--- EXPORT USED ---\n");
        if (make_export(data, ex) == 1)
            return (1);
        return (0);
    }
    else if (ft_strcmp(data->data, "unset") == 0)
    {
        printf("UNSET USED\n");
        if (make_unset(data, ex) == 1)
            return (1);
        return (0);
    }
    return (-1);
}
