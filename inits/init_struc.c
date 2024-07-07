/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:27:09 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/06 23:31:27 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*t_commands *init_cmd(void)
{
    t_commands *cmd;

    cmd = (t_commands *)malloc(sizeof(t_commands));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->args = (char **)malloc(sizeof(char *) * )
}*/

void    init_exec_structure(t_exec *ex, char **envp)
{
    int env_i;
    int i;

    ex->prev_pipe = -1;
    ex->pipefd[0] = -1;
    ex->pipefd[1] = -1;
    env_i = 0;
    while (envp[env_i])
        env_i++;
    printf("%d\n", env_i);
    ex->env = malloc(sizeof(char *) * (env_i + 1));
    if (ex->env == NULL)
    {
        ft_putstr_fd("Minishell: malloc: allocation memory failed\n", 2);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < env_i)
    {
        ex->env[i]= ft_strdup(envp[i]);
        i++;
    }
    ex->env[env_i] = NULL;
    //print_array(ex->env);
}

void    free_exec_structure(t_exec *ex)
{
    int i;

    i = 0;
    if (ex->env != NULL)
    {
        while (ex->env[i])
        {
            free(ex->env[i]);
            i++;
        }
        free(ex->env);
    }
}