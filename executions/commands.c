/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/09 13:14:15 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_command(t_input_data *data, t_exec *ex)
{
	//printf("***---IN_EXEC_COMMAND\n");
	if (!data->args || !data->args[0])
	{
		ft_putstr_fd("Minishell: command not found\n", 2);
		exit(127);
	}
	//print_node(data.cmd_lst);
	//if (get_builtin(data.cmd_lst->cmd) == 0)
		
	//printf("cmd = %s\n", data.cmd_lst->cmd);
	//printf("cmd->data_type = %d\n", data.cmd_lst->cmd_type);
	if (data->cmd_type == 1 && data->exec_fail == -1)
	//if (data.cmd_lst->input_type != -1 || data.cmd_lst->output_type != -1)
	{
		if (get_builtin(data, ex) == 0)
			exit(EXIT_SUCCESS);
		//get_builtin pas terminée
		make_path(ex, &data);
		if (data->path == NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(data->data, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		//printf("before execve : cmd = %s\n", cmd->data);
		if (execve(data->path, data->args, ex->env) == -1)
		{
        	write (2, "Error : execve\n", 16);
        	exit(127);
    	}
	}
}

/*void   make_child(t_input_data *cmd, int prev_pipe, int pipefd[2], t_exec *ex)
{
	pid_t	pid;
	//int		status;

	printf("in make child\n");
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : fork creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
		if (cmd->next && cmd->next->pipe_type == 1)
		{
			close(pipefd[READ_END]);
			dup2(pipefd[WRITE_END], STDOUT_FILENO);
			close(pipefd[WRITE_END]);
		}
		
		print_node(cmd);
		open_all(cmd);
		if (cmd->data_type == 1 && cmd->file_type != 1 && cmd->exec_fail != 1)
		{
			//printf("cmd = %s\n", cmd->args[0]);
			//printf("using cmd : %s\n", cmd->args[0]);
			exec_command(cmd, ex->env);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		if (cmd->next && cmd->next->pipe_type == 1)
			close(pipefd[WRITE_END]);
		if (prev_pipe != -1)
			close(prev_pipe);
		//waitpid(pid, &status, 0);
		//printf("in parent process\n");
	}
}*/

/*static void open_redirections(t_input_data *cmd)
{
    if (cmd->output_type != -1)
    {
        int flags = O_WRONLY | O_CREAT;
        if (cmd->output_type == 2)  // >
            flags |= O_TRUNC;
        else if (cmd->output_type == 3)  // >>
            flags |= O_APPEND;
        
        int fd = open(cmd->output, flags, 0644);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    if (cmd->input_type != -1)
    {
        int fd = open(cmd->input, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}*/

/*static void	exec_all_command(t_input_data *start, t_input_data *end, t_exec *ex)
{
	t_input_data	*cmd;
	t_input_data	*last_redirect;

	cmd = start;
	last_redirect = NULL;
	while (cmd != end)
	{
		printf("cmd = %s\n", cmd->data);
		//printf("exec_all_command : cmd = %s\n", cmd->data);
		if (cmd->input_type != -1 || cmd->output_type != -1)
		{
			printf("redirection founded\n");
			last_redirect = cmd;
		}
		else if (cmd->data_type == 1)
		{
			printf("command founded\n");
			if (last_redirect)
			{
				//open_input(last_redirect);
				//open_output(last_redirect);
				open_redirections(last_redirect);
			}
			printf("using exec_command\n");
			exec_command(cmd, ex);
			return;
		}
		cmd = cmd->next;
	}
	printf("no command found\n");
	if (last_redirect)
		open_redirections(last_redirect);
}*/

void	make_child(t_input_data *start, t_input_data *end, t_exec *ex)
{
	pid_t			pid;
	t_input_data	*cmd;

	printf("--- IN MAKE CHILD\n");
	printf("cmd start = %s\n", start->data);
	/*if (end)
		printf("cmd end = %s\n", end->data);
	else
		printf("cmd end = NULL\n");*/
	printf("		-----\n");
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork: creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (ex->prev_pipe != -1)
		{
			dup2(ex->prev_pipe, STDIN_FILENO);
			close(ex->prev_pipe);
		}
		if (end && end->pipe_type == 1)
		{
			close(ex->pipefd[READ_END]);
			dup2(ex->pipefd[WRITE_END], STDOUT_FILENO);
			close(ex->pipefd[WRITE_END]);
		}
		//printf("BEFORE MAKE_ALL_REDIRECTION\n");
		make_all_redirections(start, end);
		//printf("BEFORE EXEC_ALL_COMMAND\n");
		//exec_all_command(start, end, ex);
		//printf("BEFORE EXEC_COMMAND\n");
		cmd = start;
		while (cmd && cmd != end)
		{
			if (cmd->cmd_type == 1)
			{
				printf("executing cmd : %s\n", cmd->data);
				exec_command(cmd, ex);
				break;
			}
			cmd = cmd->next_data_same_command_id;
		}
		//printf("no command found or execution is finished\n");
		//exit(EXIT_FAILURE);
	}
	else
		printf("in parent process : child pid is %d\n", pid);
}