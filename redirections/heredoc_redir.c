/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:28:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/08 22:29:00 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void	make_input_heredoc(char *input)
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
}*/