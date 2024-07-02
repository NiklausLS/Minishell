/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/02 16:10:41 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

static void	exec_command(t_commands *cmd, char **envp)
{
    t_data data;
	
	printf("---IN_EXEC_COMMAND\n");
	data.cmd_lst = cmd;
	if (data.cmd_lst->cmd_type == 1) //|| data.cmd_lst->output_type != -1 || data.cmd_lst->pipe_type == 1)
	{
		make_path(envp, &data);
		printf("exec_command : cmd = %s\n", data.cmd_lst->cmd);
		printf("exec_command : path = %s\n", data.cmd_lst->path);
		printf("exec_command : args = %s\n", data.cmd_lst->args[0]);
		printf("exec_command : input = %s\n", data.cmd_lst->input);
		printf("exec_command : output = %s\n", data.cmd_lst->output);
	
		if (data.cmd_lst->path == NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd->cmd, 2);
			ft_putstr_fd(": Command not found\n", 2);
			exit(EXIT_FAILURE);
		}
		if (execve(data.cmd_lst->path, cmd->args, envp) == -1)
		{
			//perror("execve");
        	write (2, "Error : execve\n", 16);
        	exit(EXIT_FAILURE);
    	}
	}
}

/*static void	do_input(t_commands *cmd, int prev_pipe)
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (cmd->next && (cmd->next->input_type == 0 || cmd->next->input_type == 1))
		make_output(cmd->next);
}

static void	do_output(t_commands *cmd, int pipefd[2])
{
	if (cmd->next && cmd->next->pipe_type == 1)
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
	else if (cmd->next && (cmd->next->input_type == 2 || cmd->next->input_type == 3))
		make_output(cmd->next);
}*/

void   make_child(t_commands *cmd, int prev_pipe, int pipefd[2], char **envp)
{
	pid_t	pid;

	printf("---IN_MAKE_CHILD\n");
	printf("cmd = %s\n", cmd->cmd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : fork creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		//if (cmd->cmd_type == 1)
		//	exec_command(cmd, envp);
		//else if (cmd->input_type != -1 || cmd->output_type != -1)
		make_all_redirections(cmd, prev_pipe, pipefd);
		exec_command(cmd, envp);
		//else if (cmd->cmd_type == 1)
		//	exec_command(cmd, envp);
	}
	else
		printf("in parent process\n");
	/*if (cmd->next && cmd->next->pipe_type == 1)
		close(pipefd[WRITE_END]);
	if (prev_pipe != -1)
		close(prev_pipe);*/
}