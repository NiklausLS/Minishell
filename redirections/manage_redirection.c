/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:17:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 19:01:17 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

int	open_input(t_commands *cmd)
{
	int	fd;
	t_commands *current;

	fd = -1;
	current = cmd;
	while (current)
	{
		if (cmd->input_type == 0)
		{
			fd = open(cmd->input, O_RDONLY, 0644);
			if (fd == -1)
			{
				print_error(1, cmd->input);
				cmd->exec_fail = 1;
			}
			return (fd);
		}
		/*else if (cmd->input_type == 1)
		{
			make_input_heredoc(cmd->input);
			return (fd);
		}*/
		current = current->next;
	}
	return (fd);
}

int	open_output(t_commands *cmd)
{
	int	fd;
	t_commands *current;

	printf("---IN MAKE OUTPUT\n");
	fd = -1;
	current = cmd;
	int i = 1;
	while (current)
	{
		printf("open_output nbr %d\n", i);
		if (current->output_type == 2)
		{
			fd = open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf("- fd = %d\n", fd);
			printf("- output = %s\n", current->output);
			if (fd == -1)
			{
				printf("blabla\n");
				print_error(1, current->output);
				printf("blabla\n");
				current->exec_fail = 1;
				current->error = 1;
			}
			//if (dup2(fd, STDOUT_FILENO) == -1)
			//	ft_putstr_fd("Minishell: Error redirecting output\n", 2);
		}
		else if (current->output_type == 3)
		{
			printf(" - cmd->output_type = 3\n");
			printf(" - cmd->output = %s\n", cmd->output);
			fd = open(current->output, O_RDWR | O_APPEND, 0644);
			if (fd == -1)
			{
				print_error(1, current->output);
				current->exec_fail = 1;
				current->error = 1;
			}
		//dup2(fd, STDOUT_FILENO);
		}
		current = current->next;
		i++;
	}
	printf("enf of open_output loop\n");
	return (fd);
}

void	open_all(t_commands *cmd)
{
	int	input_fd;
	int	output_fd;

	input_fd = open_input(cmd);
	printf("final input fd is %d and his input is : %s\n", input_fd, cmd->input);
	output_fd = open_output(cmd);
	printf("final output fd is %d and his output is : %s\n", output_fd, cmd->output);
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != 1)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	make_all_redirections(t_commands *cmd, int prev_pipe, int pipefd[2])
{
	printf("in make_all_redirections\n");
	printf("input_type = %d\n", cmd->input_type);
	printf("output_type = %d\n", cmd->output_type);
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
	if (cmd->input_type == 0 || cmd->input_type == 1)
	{
		printf(" * unsing make_input in make all redirections\n");
		printf(" * * cmd->input_type = %d et cmd->input = %s\n", cmd->input_type, cmd->input);
		open_input(cmd);
	}
	else if (cmd->output_type == 2 || cmd->output_type == 3)
	{
		printf(" * unsign make_output in make all redirections\n");
		printf(" * * cmd->output_type = %d et cmd->output = %s\n", cmd->output_type, cmd->output);
		open_output(cmd);
	}
}
