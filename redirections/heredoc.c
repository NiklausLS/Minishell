/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:12:46 by nileempo          #+#    #+#             */
/*   Updated: 2024/08/08 10:39:27 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static int	make_heredoc(t_token *data)
{
	int		fd;
	char	*here;

	here = readline_heredoc(data);
	if (!here)
		return (-1);
	fd = 

}*/

/*
 * Loop prompt and add /n
 */
/*char    *readline_heredoc(t_token *delim)
{
    char    *line;
    char    *here;
    char    *tmp;

    here = NULL;
    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if (ft_strcmp(line, delim) == 0)
        {
            free(line);
            break ;
        }
        tmp = ft_strjoin(here, "\n");
        free(here);
        here = ft_strjoin(tmp, line);
        free(tmp);
        free(line);
    }
    return (here);
}*/



























/*int main(int argc, char *argv[]) {
    char *heredoc_content = NULL;

    if (heredoc(&heredoc_content, "EOF") == 0) {
        printf("Heredoc content:\n%s\n", heredoc_content);
    } else {
        printf("Error occurred during heredoc\n");
    }
    printf("%d\n%s\n", argc, argv[0]);

    if (heredoc_content)
        free(heredoc_content);

    return 0;
}*/
/*
    LES SIGNAUX CTRL C ETC A REPRENDRE REGARDER ANCIEN GPT
    int ctrl_d;

    ctrl_d = handle_eof();
    ici
    //ctrl_d exit shell even if line being read
    while(global_signal_received != SIGINT && (handle_eof() == 0))
    {
       ctrl_d = handle_eof();
    }
    return (0);
    */

/*
   Fermeture des descripteurs de fichiers : Assure-toi que tous les descripteurs de fichiers ouverts sont correctement fermés avant de quitter. Cela inclut notamment les fichiers ouverts à l'aide de open() et close(), ainsi que d'autres descripteurs de fichiers comme ceux associés aux pipes ou aux redirections.
*/