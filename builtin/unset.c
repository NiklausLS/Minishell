/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:26:09 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/08 14:15:12 by nileempo         ###   ########.fr       */
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
    int size;

    i = 0;
    size = ft_strlen(var);
    printf("- * in get_index\n");
    printf("- * var = %s\n", var);

    while (ex->env[i])
    {
        if (ft_strncmp(ex->env[i], var, size) == 0)
        {
            printf("- * var found at : %d\n", i);
            return (i);
        }
        i++;
    }
    printf("- * var not found\n");
    return (-1);
}

static void delete_var(t_exec *ex, int index)
{
    printf("- - * in delete_var\n");
    printf("- - * deleting %s\n", ex->env[index]);
    free(ex->env[index]);
    ex->env[index] = NULL;
    while (ex->env[index + 1])
    {
        ex->env[index] = ex->env[index + 1];
        index++;
    }
    ex->env[index] = NULL;
    printf("- - * ex->env[%d] = %s\n", index, ex->env[index]);
}

int make_unset(t_commands *cmd, t_exec *ex)
{
    int index;

    if (cmd->next == NULL)
    {
        printf("- not enought argument to use unset\n");
        return (-1);
    }
    printf("- in make_unset\n");
    printf("- env before\n");
    //print_env(ex);
    index = get_index(ex, cmd->next->cmd);
    printf("- index = %d\n", index);
    if (index != -1)
        delete_var(ex, index);
    printf("- env after\n");
    //print_env(ex);
    return (0);
}