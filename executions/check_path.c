/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:12:42 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/24 12:11:09 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*
 * Get path from the envp
 */
static void	get_path(char **envp, t_data *data)
{
	t_data *current;

	current = data;
	printf("--- IN GET PATH\n");

	//if (envp == NULL || *envp == NULL)
	//	return ;
	//printf("--- IN GET PATH\n");
	//print_array(data->env);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			while (current)
			{
				current->path = *envp + 5;
				//printf("current path = %s\n", current->path);
				current = current->next;
			}
			return ;
		}
		envp++;
	}
}

/*
 * Split the path i got and add / at the end
 */
static void	split_path(t_data *data)
{
	char	*tmp;
	int		i;

	//get_path(envp, data);
	printf("--- IN SPLIT PATH\n");
	if (data->path == NULL)
		return ;
	//printf("data->path = %s\n", data->path);
	data->env = ft_split(data->path, ':');
	if (data->env == NULL)
		return ;
	//printf("BEFORE\n");
	//print_array(data->env);
	i = 0;
	while (data->env[i])
	{
		tmp = data->env[i];
		data->env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	//printf("AFTER\n");
	//print_array(data->env);
}

/*
static void	check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			free(cmd);
			ft_errorexit("No such file or directory\n");
		}
		i++;
	}
}*/

/*
 * check if the path is ok and stores it
 */
static char	*check_path(char *cmd, t_data *data)
{
	int		i;

	i = 0;
	printf("--- IN CHECK PATH = %s\n", data->cmd);
	if (cmd == NULL || cmd[0] == '\0')
		ft_errorexit("check path : Command not found\n");
	if (access(cmd, F_OK | X_OK) == 0)
	{
		data->path = ft_strdup(cmd);
		printf("check path : path ok\n");
		return (data->path);
	}
	//check_cmd(cmd);
	if (data->env == NULL || data->env[0] == NULL)
		ft_errorexit("check path : No such file or directory\n");
	while (data->env[i])
	{
		data->path = ft_strjoin(data->env[i], cmd);
		if (access(data->path, F_OK | X_OK) == 0)
		{
			printf("check path : cmd %s is OK\n", data->cmd);
			return (data->path);
		}
		i++;
	}
	data->path = NULL;
	print_array(&data->path);
	return (data->path);
}

void	make_path(char **envp, t_data *data, char *cmd)
{
	get_path(envp, data);
	split_path(data);
	check_path(cmd, data);
}
