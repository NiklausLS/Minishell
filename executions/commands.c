/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/24 10:27:22 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

static void	make_pipe(t_data *data)
{
	if (data->next)
	{
		if (pipe(data->pipefd) == -1)
		{
			ft_putstr_fd("pipe creation failed\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

static int	make_fork(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static	void	make_redirections(t_data *data, int input_fd)
{
	if (input_fd != 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (data->next != NULL)
	{
		dup2(data->pipefd[1], 1);
		close(data->pipefd[1]);
	}
	if (data->next != NULL)
		close(data->pipefd[0]);
}

static void	make_exec_path(t_data *data)
{
	if (data->path == NULL)
	{
		make_path(data->env, data, data->cmd);
		if (data->path == NULL)
		{
			ft_putstr_fd(" test", 2);
			printf("%s", data->cmd);
			ft_putstr_fd("Command not found\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	exec_command(t_data *head)
{
    t_data *current;
    int     input_fd;
	int		pid;

    current = head;
	input_fd = 0;
    while (current)
    {
        make_pipe(current);
		pid = make_fork();
        if (pid == 0)
		{
			make_redirections(current, input_fd);
			make_exec_path(current);
		}
        if (input_fd != 0)
            close(input_fd);
        if (current->next != NULL)
            close(current->pipefd[1]);
        input_fd = current->pipefd[0];
        current = current->next;
    }
}

/*
void   make_child(t_data *data, char **env)
{
    if (execve(data->path, &data->cmd, env) == -1)
    {
        write (2, "Error : execve\n", 16);
        exit(EXIT_FAILURE);
    }
}*/