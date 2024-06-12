/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:17:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/12 12:22:31 by nileempo         ###   ########.fr       */
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

/*
static int	output_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			printf("output_redirection : > found.\n");
			return (0);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			printf("output_redirection : >> found.\n");
			return (1);
		}
		i++;
	}
	return (-1);
}*/

//check if a pipe is present
/*static int	check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			return (0);
		}
		i++;
	}
	return (-1);
}*/

//open the file and use the right flag depending of the operator
//will handle the file opener depending of the operator ?
//PAS COMPLETE : IL FAUT GERER LES RISQUES D ERREUR
void    make_redirection(char *str)
{
	int	fd;

    if (check_redirection(str) == 0)
	{
		fd = protected_open(str, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	/*else if (check_redirection(str, ???) == 1)
	{
		//voir pour le here_doc
	}*/
	else if (check_redirection(str) == 2)
	{
		fd = protected_open(str, O_WRONLY);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		//écrit direct, ne lit pas et donc écrase.
	}
	else if (check_redirection(str) == 3)
	{
		fd = protected_open(str, O_RDWR | O_APPEND);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		//lit puis écrit après
	}
}

//TO DO LIST : vérifier les différences entre tous les opérateurs
//pour les ouvertures du fichier
//finir exec pour le here doc