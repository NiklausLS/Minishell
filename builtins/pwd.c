/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:39:16 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/27 00:11:04 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_pwd(void)
{
	char	*repertory;

	repertory = getcwd(NULL, 0);
	if (repertory == NULL)
	{
		ft_putstr_fd("Minishell: pwd error\n", 2);
		return (1);
	}
	printf("%s\n", repertory);
	free(repertory);
	return (0);
}
