/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:08:18 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 22:57:54 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dup_input(int fd)
{
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 input error\n", 2);
			protected_close(fd);
			return (1);
		}
		protected_close(fd);
	}
	return (0);
}

static int	dup_output(int fd)
{
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Minishell: dup2 output error\n", 2);
			protected_close(fd);
			return (1);
		}
		protected_close(fd);
	}
	return (0);
}

int	make_dup_and_close(int last_input, int last_output)
{
	if (last_input == -1 && last_output == -1)
		return (0);
	if (last_input != -1)
		if (dup_input(last_input) == 1)
			return (1);
	if (last_output != -1)
		if (dup_output(last_output) == 1)
			return (1);
	if (last_input != -1)
		close (last_input);
	if (last_output != -1)
		close (last_output);
	return (0);
}
