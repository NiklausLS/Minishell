/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:17:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/04 19:46:28 by nileempo         ###   ########.fr       */
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
	make_heredoc(pipefd[WRITE_END], input);
	close(pipefd[WRITE_END]);
	dup2(pipefd[READ_END], STDIN_FILENO);
	close(pipefd[READ_END]);
}

void	make_input(t_commands *cmd)
{
	int	fd;

	printf("---IN_MAKE_INPUT\n");
	if (cmd->input_type == 0)
	{
		cmd->input = ft_strdup(cmd->cmd);
		//cmd->next->input = ft_strdup(cmd->next->cmd);
		printf("OPEN = %s\n", cmd->input);
		fd = open(cmd->input, O_RDONLY, 06440);
		if (fd == -1)
		{
			ft_putstr_fd("Error : open\n", 2);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->input_type == 1)
		make_input_heredoc(cmd->input);
}

void	make_output(t_commands *cmd)
{
	int	fd;

	printf("---IN MAKE OUTPUT\n");
	if (cmd->output_type == 2)
	{
		//printf("cmd->output_type = 2\n");
		cmd->output = ft_strdup(cmd->output);
		//printf("cmd->output = %s\n", cmd->output);
		//cmd->output = ft_strdup(cmd->output);
		//cmd->next->cmd = NULL;
		//cmd->cmd = NULL;
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("Error : open\n", 2);
			exit(EXIT_FAILURE);
		}
		//printf("%s have been opened\n", cmd->output);
		//printf("redirecting output\n");
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: Error redirecting output\n", 2);
			exit(EXIT_FAILURE);
		}
		close(fd);
		//printf("output have been redirected\n");
	}
	else if (cmd->output_type == 3)
	{
		printf("cmd->output_type = 3\n");
		cmd->output = ft_strdup(cmd->output);
		printf("cmd->output = %s\n", cmd->output);
		//cmd->output = ft_strdup(cmd->output);
		fd = open(cmd->output, O_RDWR | O_APPEND);
		if (fd == -1)
		{
		ft_putstr_fd("Error : open\n", 2);
		exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

//A REVOIR
void	make_heredoc(int fd, char *delim)
{
	char	*str;
	size_t	len;
	ssize_t	read;

	printf("---IN_MAKE_HEREDOC\n");
	printf("Heredoc> ");
	while ((read = getline(&str, &len, stdin)) != -1)
	{
		if (ft_strncmp(str, delim, ft_strlen(delim)) == 0
			&& (str[ft_strlen(delim)] == '\n'
				|| str[ft_strlen(delim)] == '\0'))
			break;
		write(fd, str, read);
		printf("Heredoc> ");
	}
	free(str);
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
		make_input(cmd);
	}
	else if (cmd->output_type == 2 || cmd->output_type == 3)
	{
		printf(" * unsign make_output in make all redirections\n");
		make_output(cmd);
	}
}
