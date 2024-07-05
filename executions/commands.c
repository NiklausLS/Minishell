/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 17:03:44 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

static void	exec_command(t_commands *cmd, char **envp)
{
    t_data data;
	
	//printf("***---IN_EXEC_COMMAND\n");
	data.cmd_lst = cmd;
	if (!cmd->args[0])
	{
		ft_putstr_fd("Minishell: Command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	//printf("cmd = %s\n", data.cmd_lst->cmd);
	//printf("cmd->cmd_type = %d\n", data.cmd_lst->cmd_type);
	if (data.cmd_lst->cmd_type == 1 && data.cmd_lst->exec_type == -1)
	{
		//get_builtin pas terminée
		make_path(envp, &data);
		if (data.cmd_lst->path == NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd->cmd, 2);
			ft_putstr_fd(": Command not found\n", 2);
			exit(EXIT_FAILURE);
		}
		if (execve(data.cmd_lst->path, cmd->args, envp) == -1)
		{
        	write (2, "Error : execve\n", 16);
        	exit(EXIT_FAILURE);
    	}
	}
	else
	{
		printf("nothing to execute in exec_command\n");
		exit(EXIT_FAILURE);
	}
}

void   make_child(t_commands *cmd, int prev_pipe, int pipefd[2], char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : fork creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		print_node(cmd);
		if (cmd->next->input_type != -1 || cmd->next->output_type != -1)
		{
			//printf("--- cmd->input_type = %d | cmd->output_type = %d\n", cmd->next->input_type, cmd->next->output_type);
			make_all_redirections(cmd->next, prev_pipe, pipefd);
			if (cmd->next->file_type != 1)
				printf("test after wrong open\n");
		}
		if (cmd->cmd_type == 1 && cmd->file_type != 1 && cmd->exec_type != 1)
		{
			//printf("cmd->cmd_type = %d\n", cmd->cmd_type);
			//printf("using cmd : %s\n", cmd->args[0]);
			exec_command(cmd, envp);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		//printf("in parent process\n");
	}
}

/*void	exec_redir(t_data *data, t_commands *cmd)
{
	int	pipe_type;

	pipe_type = 0;
	if (cmd->input)
		
}*/