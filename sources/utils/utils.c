/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:16:31 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/10 05:26:46 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**custom_realloc(char **env, int old_size, int new_size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[old_size] = NULL;
	free(env);
	return (new_env);
}
