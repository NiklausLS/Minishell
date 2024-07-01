/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:26:24 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 21:39:09 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

int	protected_open(char *file, int flags)
{
	int	fd;

	fd = open(file, flags);
	if (fd == -1)
	{
		ft_putstr_fd("Error : open\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	protected_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error : pipe/n", 2);
		exit(EXIT_FAILURE);
	}
}
