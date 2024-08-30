/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:12:46 by nileempo          #+#    #+#             */
/*   Updated: 2024/08/30 11:57:02 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//trouver un moyen de supprimer le fichier temporaire après utilisation
int	make_heredoc(char *cmd)
{
	int		fd;
	char	*here;

    //printf("--- IN MAKE HEREDOC\n");
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
    close(fd);
    //printf("---END OF MAKE HEREDOC\n");
    return (fd);
}

/*
 * join and free here and line strings
 */
static char *join_and_free(char *s1, char *s2)
{
	char	*res;

    //printf("---- IN JOIN AND FREE\n");
	res = ft_strjoin(s1, s2);
	free(s1);
    //printf("---- END OF JOIN AND FREE\n");
	return (res);
}
/*
 * Loop prompt and add /n
 */
char    *readline_heredoc(char *delim)
{
    char    *line;
    char    *here;

    //printf("----- IN READLINE\n");
    //printf("delim = %s\n", delim);
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
    //printf("----- END OF READLINE\n");
    return (here);
}
