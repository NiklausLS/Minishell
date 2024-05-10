/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:00:22 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/10 23:56:43 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list
//CD
void    get_builtin(t_data *data)
{
    if (strcmp(data->cmd, "cd") == 0)
    {
        printf("CD USED\n");
        cd(data->path);
    }
    else if (strcmp(data->cmd, "echo") == 0)
    {
        printf("ECHO USED\n");
    }
    else if (strcmp(data->cmd, "pwd") == 0)
    {
        printf("PWD USED\n");
    }
    else if (strcmp(data->cmd, "export") == 0)
    {
        printf("EXPORT USED\n");
    }
    else if (strcmp(data->cmd, "unset") == 0)
    {
        printf("UNSET USED\n");
    }
    else if (strcmp(data->cmd, "env") == 0)
    {
        printf("ENV USED\n");
    }
    else if (strcmp(data->cmd, "exit") == 0)
    {
        printf("EXIT USED\n");
    }
}