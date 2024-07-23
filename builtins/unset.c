/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:26:09 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/23 15:21:34 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int make_unset(t_token *data, t_exec *ex)
{
    int index;

    printf("--- IN MAKE UNSET\n");
    if (data->next == NULL)
    {
        printf("- nothing to unset\n");
        return (0);
    }
    printf("- in make_unset\n");
    printf("- env before\n");
    //print_env(ex);
    index = get_index(ex, data->next->value);
    printf("- index = %d\n", index);
    if (index != -1)
        delete_var(ex, index);
    printf("- env after\n");
    //print_env(ex);
    return (0);
}