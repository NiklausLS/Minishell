/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:26:24 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/30 20:23:13 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * make a pipe and check if it's ok
 */
int	protected_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Minishell: pipe failed/n", 2);
		return (1);
	}
	return (0);
}

int	protected_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Minishell");
		return (1);
	}
	return (0);
}
