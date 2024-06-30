/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:17:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/29 21:53:55 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//check the operator sign
//redirige la sortie
//> delete file
//>> add to file
/*
 * @param a string
 * @returns 0 if > is found
 * @returns 1 if >> is found
 * @returns -1 if none of them is found
*/

//open the file and use the right flag depending of the operator
//will handle the file opener depending of the operator ?
void	make_redirection(char *str)
{
	int	fd;
	int	redir;

	redir = check_redirection(str);
	//printf("in make_redirections\n");
	if (redir == 0)
	{
		fd = protected_open(str + 1, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir == 2)
	{
		fd = protected_open(str + 1, O_WRONLY | O_CREAT | O_TRUNC);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir == 3)
	{
		fd = protected_open(str + 3, O_RDWR | O_APPEND);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

//TO DO LIST : vérifier les différences entre tous les opérateurs
//pour les ouvertures du fichier
//finir exec pour le here doc
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
