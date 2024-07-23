/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:53:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/23 17:12:12 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Check if there is a redirection token and return a value depending of it
 * return -1 if nothing is found
 */
int	check_redirection(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str && str[i])
	{
		if (str[i] == '<')
		{
			if (str[i] == '<' && str[i + 1] == '<')
				return (1);
			else
				return (0);
		}
		else if (str[i] == '>')
		{
			if (str[i] == '>' && str[i + 1] == '>')
				return (3);
			else
				return (2);
		}
		i++;
	}
	return (-1);
}

/*
 * Check if there is a pipe in the node
 */
int	check_pipe(char *str)
{
	if (str == NULL)
		return (-1);
	if (str[0] == '|')
		return (0);
	return (-1);
}
