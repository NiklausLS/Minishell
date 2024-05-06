/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:26:24 by nileempo          #+#    #+#             */
/*   Updated: 2024/04/20 12:47:43 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

int	protected_open(char *file_name, int flags)
{
	int	fd;

	fd = open(file_name, flags);
	if (fd == -1)
	{
		write (2, "Error: open failed\n", 20);
		exit(EXIT_FAILURE);
	}
	return (fd);
}