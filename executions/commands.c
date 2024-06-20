/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/20 21:59:10 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*
 * check if the command is a built-in first
 * if not check if it's a regular command
*/
void	exec_command(t_data *data, char **argv, char **envp)
{
    pid_t   pid;
    int     status;

    pid = fork();
    if (pid < 0)
    {
        ft_putstr_fd("fork error\n", 2);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(data->path, argv, envp) == -1)
        {
            ft_putstr_fd("execve error\n", 2);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        while (waitpid(pid, & status, WUNTRACED > 0))
        {
            if (WIFEXITED(status) || WIFSIGNALED(status))
                break;
        }
    }
}



void   make_child(t_data *data, char **env)
{
    if (execve(data->path, &data->cmd, env) == -1)
    {
        write (2, "Error : execve\n", 16);
        exit(EXIT_FAILURE);
    }
} 