/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:47:45 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/24 15:58:03 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Init my exec structure
 * Copy the envp to make a environement specific to minishell
 * @return : 0 if everything is ok, 1 if malloc failed for envp
 */
int	init_exec_structure(t_exec *ex, char **envp)
{
	int	env_i;
	int	i;

	ex->prev_pipe = -1;
	ex->pipefd[0] = -1;
	ex->pipefd[1] = -1;
	env_i = 0;
	while (envp[env_i])
		env_i++;
	ex->env = malloc(sizeof(char *) * (env_i + 1));
	if (ex->env == NULL)
	{
		ft_putstr_fd("Minishell: malloc: allocation memory failed\n", 2);
		return (1);
	}
	i = 0;
	while (i < env_i)
	{
		ex->env[i] = ft_strdup(envp[i]);
		if (ex->env[i] == NULL)
		{
			while (--i >= 0)
				free(ex->env[i]);
			free(ex->env);
			return (1);
		}
		i++;
	}
	ex->env[env_i] = NULL;
	return (0);
}
