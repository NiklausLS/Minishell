/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:12:46 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/27 00:04:43 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//trouver un moyen de supprimer le fichier temporaire après utilisation
int	make_heredoc(char *cmd)
{
	int		fd;
	char	*here;

	here = readline_heredoc(cmd);
	if (!here)
		return (-1);
	fd = open(".hidden_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(here);
		ft_putstr_fd("Error : heredoc\n", 2);
		return (1);
	}
	write (fd, here, ft_strlen(here));
	free(here);
	protected_close(fd);
	return (fd);
}

/*
 * join and free here and line strings
 */
static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
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
