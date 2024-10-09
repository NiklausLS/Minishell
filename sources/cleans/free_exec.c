/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:05:19 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 20:56:54 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Free a simple array
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
 * Free the environement
 */
int	free_exec_structure(t_exec *ex)
{
	int	i;

	i = 0;
	if (ex->env != NULL)
	{
		while (ex->env[i])
		{
			free(ex->env[i]);
			i++;
		}
		free(ex->env);
	}
	return (0);
}
