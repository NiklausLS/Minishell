/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:26 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/13 15:50:46 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int setup_pipes(t_exec *ex)
{
    if (pipe(ex->pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }
    printf("setup_pipe OK\n");
    return (0);
}

int setup_in_and_out(t_exec *ex)
{
    if (ex->prev_pipe != STDIN_FILENO)
    {
        dup2(ex->prev_pipe, STDIN_FILENO);
        close(ex->prev_pipe);
    }
    if (ex->pipefd[1] != STDOUT_FILENO)
    {
        dup2(ex->pipefd[1], STDOUT_FILENO);
        close(ex->pipefd[1]);
    }
    return (0);
}

int execute_piped_command(t_input_data *cmd, int in_fd, int out_fd, t_exec *ex)
{
    pid_t pid;
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        if (in_fd != STDIN_FILENO)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        if (make_all_redirections(cmd, NULL) == 1)
            return (1);
        exec_command(cmd, ex);
        exit(EXIT_FAILURE);
    }
    return (0);
}

void    setup_pipe_end(t_exec *ex)
{
    close(ex->pipefd[1]);
    if (ex->prev_pipe != STDIN_FILENO)
        close(ex->prev_pipe);
    ex->prev_pipe = ex->pipefd[0];
}

/*static void close_pipe(int pipefd[2])
{
    close(pipefd[0]);
    close(pipefd[1]);
}*/
