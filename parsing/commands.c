/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/11 07:26:03 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*
 * Get path from the envp
 */
static void	get_env(char **envp, t_data *data)
{
	if (envp == NULL || *envp == NULL)
		return ;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			data->path = *envp + 5;
			return ;
		}
		envp++;
	}
}

void	split_path(char **envp, t_data *data)
{
	char	*tmp;
	
	get_env(envp, data);
	printf("data->path = %s\n", data->path);

	data->split_args = ft_split(data->path, ':');
	printf("BEFORE\n");
	print_array(data->split_args);
	int i = 0;
	while (data->split_args[i])
	{
		tmp = ft_strjoin(data->split_args[i], "/");
		free(data->split_args[i]);
		data->split_args[i] = tmp;
		i++;
	}
	printf("AFTER\n");
	print_array(data->split_args);
}