/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:12:42 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/07 02:09:16 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*
 * Get path from the ex->env
 */
/*static void	get_path(t_exec *ex, t_data *data)
{
	//t_commands *current;
	int		i;
	char	*path;

	//current = data->cmd_lst;
	printf("--- IN GET PATH\n");
	printf("data->cmd_lst->cmd = %s\n", data->cmd_lst->cmd);
	i = 0;
	path = NULL;
	if (ex->env == NULL || *ex->env == NULL)
		return ;
	//printf("--- IN GET PATH\n");
	//print_array(data->env);
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], "PATH=", 5) == 0)
		{
			path = ex->env[i] + 5;
			break;
		}
		i++;
	}
	data->cmd_lst->path = path;
	printf("PATH = %s\n");
}*/


/*
 * Split the path i got and add / at the end
 */
/*static void	split_path(t_data *data)
{
	char	*tmp;
	int		i;

	//get_path(ex->env, data);
	//printf("--- IN SPLIT PATH\n");
	if (data->cmd_lst->path == NULL)
		return ;
	//printf("data->path = %s\n", data->cmd_lst->path);
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
	//print_array(data->cmd_lst->env);
}*/

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
/*static char	*check_path(t_data *data)
{
	int		i;
	char	*cmd;

	i = 0;
	//printf("--- IN CHECK PATH\n");
	//printf("cmd = %s\n", data->cmd_lst->args[0]);
	cmd = data->cmd_lst->args[0];
	if (cmd == NULL || cmd[0] == '\0')
		ft_errorexit("Minishell : Command not found\n");
	if (access(cmd, F_OK | X_OK) == 0)
	{
		data->cmd_lst->path = ft_strdup(cmd);
		//printf("check path : path ok\n");
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
			//printf("check path : cmd %s is OK\n", data->cmd_lst->args[0]);
			//printf("check path : path = %s\n", data->cmd_lst->path);
			return (data->cmd_lst->path);
		}
		i++;
	}
	data->cmd_lst->path = NULL;
	//print_array(&data->cmd_lst->path);
	//printf("data->cmd_lst->path = %s\n", data->cmd_lst->path);
	return (data->cmd_lst->path);
}*/

static void get_path(t_exec *ex, t_data *data)
{
    char *path = NULL;
    int i = 0;

    //printf("--- IN GET PATH\n");
    //printf("data->cmd_lst->cmd = %s\n", data->cmd_lst->cmd);
    if (ex->env == NULL || *ex->env == NULL)
        return;
    while (ex->env[i])
    {
        if (ft_strncmp(ex->env[i], "PATH=", 5) == 0)
        {
            path = ex->env[i] + 5;
            break;
        }
        i++;
    }
    data->cmd_lst->path = path;
    //printf("PATH found: %s\n", path ? path : "Not found");
}

static char **split_path(char *path)
{
    char **paths;
	char *tmp;
    int i;

	paths = ft_split(path, ':');
	tmp = NULL;
	i = 0;
    if (!paths)
        return NULL;
    while (paths[i])
    {
        tmp = paths[i];
        paths[i] = ft_strjoin(tmp, "/");
        free(tmp);
        i++;
    }
    return (paths);
}

static char *find_command(char **paths, char *cmd)
{
    int i = 0;
    char *full_path;

    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], cmd);
        if (access(full_path, F_OK | X_OK) == 0)
            return full_path;
        free(full_path);
        i++;
    }
    return (NULL);
}

static void check_and_set_path(t_commands *cmd)
{
    char **paths;
	int	i;

	if (!cmd->path)
        return;
	paths = split_path(cmd->path);
	i = 0;
    if (paths)
    {
        cmd->path = find_command(paths, cmd->args[0]);
		while (paths[i])
		{
            free(paths[i]);
			i++;
		}
        free(paths);
    }
    if (!cmd->path && access(cmd->args[0], F_OK | X_OK) == 0)
        cmd->path = ft_strdup(cmd->args[0]);
    //printf("Command: %s, Path: %s\n", cmd->args[0], cmd->path ? cmd->path : "Not found");
}

void make_path(t_exec *ex, t_data *data)
{
    t_commands *current;
	
	current = data->cmd_lst;
    //printf("--- IN_MAKE_PATH\n");
    get_path(ex, data);
    while (current)
    {
        if (current->cmd_type == 1)
            check_and_set_path(current);
        current = current->next;
    }
}

/*void	make_path(t_exec *ex, t_data *data)
{
	printf("launching get_path\n");
	printf("--- IN_MAKE_PATH\n");
	get_path(ex, data);
	//split_path(data);
	//check_path(data);
}*/


