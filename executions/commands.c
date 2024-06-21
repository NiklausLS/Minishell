/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/21 15:39:34 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void	exec_command(t_data *head)
{
    t_data *current;
    int     input_fd;

    current = head;
    while (current)
    {
        if (current->next != NULL)
            if (pipe(current->pipefd) == -1)
            {
                ft_putstr_fd("error : pipe failed\n", 2);
                exit(EXIT_FAILURE);
            }
    
        if (fork() == 0)
        {
            if (input_fd != 0)
            {
                dup2(input_fd, 0);
                close (input_fd);
            }
            if (current->next != NULL)
            {
                dup2(current->pipefd[1], 1);
                close(current->pipefd[1]);
            }
            if (current->next != NULL)
                close(current->pipefd[0]);
        }
        if (current->path == NULL)
        {
            make_path(current->env, current, current->cmd);
            if (current->path == NULL)
            {
                printf("%s", current->cmd);
                ft_putstr_fd("Command not foud\n", 2);
                exit(EXIT_FAILURE);
            }
        }
        if (input_fd != 0)
            close(input_fd);
        if (current->next != NULL)
            close(current->pipefd[1]);
        input_fd = current->pipefd[0];
        current = current->next;
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