/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/30 07:23:15 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

static void	make_input_heredoc(char *input)
{
	int	pipefd[2];
	
	printf("---IN_MAKE_INPUT_HEREDOC\n");
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("heredoc pipe failed\n", 2);
		exit(EXIT_FAILURE);
	}
	make_heredoc(pipefd[WRITE_END], input + 2);
	close(pipefd[WRITE_END]);
	dup2(pipefd[READ_END], STDIN_FILENO);
	close(pipefd[READ_END]);
}

static void	make_input(t_commands *cmd, int	prev_pipe)
{
	int	input_red;

	printf("---IN_MAKE_INPUTE\n");
	input_red = check_redirection(cmd->input);
	if (input_red == -1)
		return ;
	if (cmd && cmd->next)
	{
		//input_red = check_redirection(cmd->input);
		if (input_red == 0)
			make_redirection(cmd->input);
		else if (input_red == 1)
			make_input_heredoc(cmd->input);
		else if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}	
	}
}

static void	make_output(t_commands *cmd, int pipefd[2])
{
	int	output_red;

	printf("---IN_MAKE_OUTPUT\n");
	output_red = check_redirection(cmd->output);
	if (output_red == -1)
		return ;
	printf("output_red = %d\n", output_red);
	if (cmd->output)
	{
		if (output_red == 2 || output_red == 3)
		{
			printf("end of make_output\n");
			make_redirection(cmd->output);
		}
	}
	else if (cmd->next != NULL)
	{
		close(pipefd[READ_END]);
		dup2(pipefd[WRITE_END], STDERR_FILENO);
		close(pipefd[WRITE_END]);
	}
	printf("end of make_output\n");
}

static void	exec_command(t_commands *cmd, char **envp)
{
    t_data data;
	
	printf("---IN_EXEC_COMMAND\n");
	data.cmd_lst = cmd;
	make_path(envp, &data);
	printf("exec_command : cmd = %s\n", data.cmd_lst->cmd);
	printf("exec_command : path = %s\n", data.cmd_lst->path);
	printf("exec_command : args = %s\n", data.cmd_lst->args[0]);
	
	if (data.cmd_lst->path == NULL)
	{
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

void   make_child(t_commands *cmd, int prev_pipe, int pipefd[2], char **envp)
{
	pid_t	pid;

	printf("---IN_MAKE_CHILD\n");
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : fork creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		make_input(cmd, prev_pipe);
		make_output(cmd, pipefd);
		//printf("before exec_command");
		exec_command(cmd, envp);
	}
}