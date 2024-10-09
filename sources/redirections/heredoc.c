/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:12:46 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 22:53:29 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_heredoc(char *cmd)
{
	int		pipefd[2];
	char	*here;

	if (protected_pipe(pipefd) == 1)
		return (1);
	here = readline_heredoc(cmd);
	if (!here)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	write(pipefd[1], here, strlen(here));
	free(here);
	if (protected_close(pipefd[1]) == 1)
		return (1);
	return (pipefd[0]);
}

/*
 * join and free here and line strings
 */
static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s2 == NULL)
	{
		free(s1);
		return (res);
	}
	else
		res = ft_strjoin(res, "\n");
	return (res);
}

/*
 * Loop prompt and add /n
 */
char	*readline_heredoc(char *delim)
{
	char	*line;
	char	*here;

	here = ft_strdup("");
	heredoc_signal();
	if (!here)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		here = join_and_free(here, line);
		free(line);
		if (!here)
			return (NULL);
	}
	return (here);
}
