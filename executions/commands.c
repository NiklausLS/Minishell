/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:52:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/23 15:12:22 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*
 * Get path from the envp
 */
static void	get_path(char **envp, t_data *data)
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

/*
 * Split the path i got and add / at the end
 */
void	split_path(char **envp, t_data *data)
{
	char	*tmp;
	int		i;
	
	get_path(envp, data);
	if (data->env == NULL)
		return ;
	printf("data->path = %s\n", data->path);
	data->env = ft_split(data->path, ':');
	if (data->env == NULL)
		return ;
	printf("BEFORE\n");
	print_array(data->env);
	i = 0;
	while (data->env[i])
	{
		tmp = data->env[i];
		data->env[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	printf("AFTER\n");
	print_array(data->env);
}

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
}

/*
 * check if the path is ok and stores it
 */
char	*check_path(char *cmd, t_data *data)
{
	int		i;

	i = 0;
	if (cmd == NULL || cmd[0] == '\0')
		ft_errorexit("command not found\n");
	if (access(cmd, F_OK | X_OK) == 0)
	{
		data->path = ft_strdup(cmd);
		return (data->path);
	}
	check_cmd(cmd);
	if (data->env == NULL || data->env[0] == NULL)
		ft_errorexit("No such file or directory\n");
	while (data->env[i])
	{
		data->path = ft_strjoin(data->env[i], cmd);
		if (access(data->path, F_OK | X_OK) == 0)
			return (data->path);
		i++;
	}
	data->path = NULL;
	return (data->path);
}
