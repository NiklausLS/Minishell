/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:17:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 17:37:50 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

static void	make_input_heredoc(char *input)
{
	int	pipefd[2];

	printf("---IN_MAKE_INPUT_HEREDOC\n");
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Minishell: heredoc pipe failed\n", 2);
		exit(EXIT_FAILURE);
	}
	make_heredoc(pipefd[WRITE_END], input);
	close(pipefd[WRITE_END]);
	dup2(pipefd[READ_END], STDIN_FILENO);
	close(pipefd[READ_END]);
}

int	make_input(t_commands *cmd)
{
	int	fd;

	printf("---IN_MAKE_INPUT\n");
	fd = 0;
	if (cmd->input_type == 0)
	{
		printf("OPEN = %s\n", cmd->input);
		fd = open(cmd->input, O_RDONLY, 0644);
		if (fd == -1)
		{
			print_error(1, cmd->input);
			cmd->exec_type = 1;
		}
		return (fd);
	}
	/*else if (cmd->input_type == 1)
	{
		make_input_heredoc(cmd->input);
		return (fd);
	}*/
	return (fd);
}

int	make_output(t_commands *cmd)
{
	int	fd;

	printf("---IN MAKE OUTPUT\n");
	fd = -1;
	if (cmd->output_type == 2)
	{
		fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error(1, cmd->output);
			cmd->exec_type = 1;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_putstr_fd("Minishell: Error redirecting output\n", 2);
		return (fd);
	}
	else if (cmd->output_type == 3)
	{
		printf("cmd->output_type = 3\n");
		printf("cmd->output = %s\n", cmd->output);
		fd = open(cmd->output, O_RDWR | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(1, cmd->output);
			cmd->exec_type = 1;
			return (fd);
		}
		//dup2(fd, STDOUT_FILENO);
		return (fd);
	}
	return (fd);
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
