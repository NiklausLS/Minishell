/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/07 14:00:06 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list
//should return 0 if succes
//anything else if error

int make_export(t_commands *cmd, t_exec *ex)
{
    int i;

    i = 1;
    if (!cmd->args[1])
    {
        while (ex->env[i])
        {
            printf("declare -x %s\n", ex->env[i]);
            i++;
        }
        return (0);
    }
    return (1);
}

