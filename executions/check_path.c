/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:12:42 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/30 07:18:13 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*
 * Get path from the envp
 */
static void	get_path(char **envp, t_data *data)
{
	t_commands *current;

	current = data->cmd_lst;
	printf("--- IN GET PATH\n");

	if (envp == NULL || *envp == NULL)
		return ;
	//printf("--- IN GET PATH\n");
	//print_array(data->env);
	while (current && *envp != NULL)
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
	//printf("current path = %s\n", current->path);
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
	if (data->cmd_lst->path == NULL)
		return ;
	//printf("data->path = %s\n", data->path);
	data->cmd_lst->env = ft_split(data->cmd_lst->path, ':');
	if (data->cmd_lst->env == NULL)
		return ;
	//printf("BEFORE\n");
	//print_array(data->env);
	i = 0;
	while (data->cmd_lst->env[i])
	{
		tmp = data->cmd_lst->env[i];
		data->cmd_lst->env[i] = ft_strjoin(tmp, "/");
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
static char	*check_path(t_data *data)
{
	int		i;
	char	*cmd;

	i = 0;
	printf("--- IN CHECK PATH = %s\n", data->cmd_lst->cmd);
	cmd = data->cmd_lst->cmd;
	if (cmd == NULL || cmd[0] == '\0')
		ft_errorexit("check path : Command not found\n");
	if (access(cmd, F_OK | X_OK) == 0)
	{
		data->cmd_lst->path = ft_strdup(cmd);
		printf("check path : path ok\n");
		return (data->cmd_lst->path);
	}
	//check_cmd(cmd);
	if (data->cmd_lst->env == NULL || data->cmd_lst->env[0] == NULL)
		ft_errorexit("check path : No such file or directory\n");
	while (data->cmd_lst->env[i])
	{
		data->cmd_lst->path = ft_strjoin(data->cmd_lst->env[i], cmd);
		if (access(data->cmd_lst->path, F_OK | X_OK) == 0)
		{
			printf("check path : cmd %s is OK\n", data->cmd_lst->cmd);
			printf("check path : path = %s\n", data->cmd_lst->path);
			return (data->cmd_lst->path);
		}
		i++;
	}
	data->cmd_lst->path = NULL;
	//print_array(&data->cmd_lst->path);
	//printf("data->cmd_lst->path = %s\n", data->cmd_lst->path);
	return (data->cmd_lst->path);
}

void	make_path(char **envp, t_data *data)
{
	//printf("launching get_path");
	printf("---IN_MAKE_PATH\n");
	get_path(envp, data);
	split_path(data);
	check_path(data);
}
