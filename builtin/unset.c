/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:26:09 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/08 09:26:51 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//undefine a variable including function

//to do list:
//-find the index of the command
//-free the command
//-change index of elements after ? 

static int get_index(t_exec *ex, char *var)
{
    int i;

    i = 0;
    printf("-- in get_index\n");
    while (ex->env[i])
    {
        if (ft_strcmp(ex->env[i], var) == 0)
        {
            printf("var found at : %d", i);
            return (i);
        }
        i++;
    }
    printf("-- var not found\n");
    return (-1);
}

int make_unset(t_commands *cmd, t_exec *ex)
{
    int index;

    if (cmd->next == NULL)
    {
        printf("not enought argument to use unset\n");
        return (-1);
    }
    printf("- in make_unset\n");
    index = get_index(ex, cmd->next->cmd);
    printf("- index = %d\n", index);
    return (0);
}