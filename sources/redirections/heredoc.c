/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:12:46 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 07:45:10 by chuchard         ###   ########.fr       */
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
	write(pipefd[1], here, ft_strlen(here));
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
	char	*res2;

	res = ft_strjoin(s1, s2);
	free(s1);
	if (s2 == NULL)
	{
		free(s1);
		return (res);
	}
	else
	{
		res2 = ft_strjoin(res, "\n");
		free(res);
		return (res2);
	}
	return (res);
}

char	*treat_signal(char *here, char *line)
{
	free(here);
	g_signal = 0;
	if (line)
		free(line);
	return (NULL);
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
		if (g_signal == 1)
			return (treat_signal(here, line));
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
