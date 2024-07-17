/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:53:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/17 22:54:05 by nileempo         ###   ########.fr       */
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
	//printf("---IN_CHECK_REDIRECTION\n");
	if (str == NULL)
	{
		//ft_putstr_fd("EMPTY STR IN CHECK REDIRECTION\n", 2);
		return (-1);
	}
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
	//printf("no redirections found\n");
	//printf("	- - - -\n");
	return (-1);
}

/*
 * Check if there is a pipe in the node
 */
int	check_pipe(char *str)
{
	printf("---IN_CHECK_PIPE\n");
	if (str == NULL)
	{
		//ft_putstr_fd("EMPTY STR IN CHECK_PIPE\n", 2);
		return (-1);
	}
	if (str[0] == '|')
	{
		//printf("str[0] = %c", str[0]);
		return (0);
	}
	return (-1);
}