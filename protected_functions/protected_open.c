/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:26:24 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/17 22:55:26 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Open a file and check if it's ok
 */
/*int	protected_open(char *file, int flags)
{
	int	fd;

	fd = open(file, flags);
	if (fd == -1)
	{
		ft_putstr_fd("Error : open\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}*/

/*
 * make a pipe and check if it's ok
 */
void	protected_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error : pipe/n", 2);
		exit(EXIT_FAILURE);
	}
}

//TO DO LIST
// - PROTECTED DUP2
// - PROTECTED CLOSE
