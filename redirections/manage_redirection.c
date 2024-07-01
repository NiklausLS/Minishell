/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:17:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 12:02:38 by nileempo         ###   ########.fr       */
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

void	make_input(t_commands *cmd)
{
	int	fd;

	printf("---IN_MAKE_INPUTE\n");
	if (cmd->input_type == 0)
	{
		fd = protected_open(cmd->cmd + 1, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->input_type == 1)
		make_input_heredoc(cmd->cmd + 2);
}

void	make_output(t_commands *cmd)
{
	int	fd;
	
	if (cmd->input_type == 2)
	{
		fd = protected_open(cmd->cmd + 1, O_WRONLY | O_CREAT | O_TRUNC);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->input_type == 3)
	{
		fd = protected_open(cmd->cmd + 1, O_RDWR | O_APPEND);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	make_heredoc(int fd, char *delim)
{
	char	*str;
	size_t	len;
	ssize_t	read;

	printf("---IN_MAKE_HEREDOC\n");
	printf("Heredoc> ");
	while ((read = getline(&str, &len, stdin)) != -1)
	{
		if (ft_strncmp(str, delim, ft_strlen(delim)) == 0 &&
			(str[ft_strlen(delim)] == '\n' || str[ft_strlen(delim)] == '\0'))
			break;
		write(fd, str, read);
		printf("Heredoc> ");
	}
	free(str);
}

void	make_all_redirections(t_commands *cmd, int prev_pipe, int pipefd[2])
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (cmd->input_type == 0 || cmd->input_type == 1)
		make_input(cmd);
	if (cmd->next && cmd->next->pipe_type == 1)
	{
		close(pipefd[READ_END]);
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
		close(pipefd[WRITE_END]);
	}
	else if (cmd->output_type == 2 || cmd->output_type == 3)
		make_output(cmd);
}