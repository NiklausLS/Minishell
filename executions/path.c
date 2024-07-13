/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:51 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/13 19:03:07 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_command(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	**split_path(char *path)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	tmp = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}

static int	check_and_set_path(t_input_data *data)
{
	char	**paths;
	char	*command_path;

	paths = split_path(data->path);
	if (!paths)
		return (1);
	command_path = find_command(paths, data->data);
	if (command_path)
	{
		if (data->path)
			free(data->path);
		data->path = command_path;
	}
	else if (access(data->data, F_OK | X_OK) == 0)
	{
		if (data->path)
			free(data->path);
		data->path = ft_strdup(command_path);
	}
	else
		return (1);
	return (0);
}

static int	get_path(t_exec *ex, t_input_data *data)
{
	int	i;

	if (ex->env == NULL || *ex->env == NULL)
		return (1);
	i = 0;
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], "PATH=", 5) == 0)
		{
			data->path = ft_strdup(ex->env[i] + 5);
			break ;
		}
		i++;
	}
	return (0);
}

int	make_path(t_exec *ex, t_input_data *data)
{
	t_input_data	*current;

	current = data;
	if (data->path)
		free(data->path);
	if (get_path(ex, data) == 1)
		return (1);
	while (current)
	{
		if (current->cmd_type == 1)
		{
			if (check_and_set_path(current) == 1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
