#include "../includes/minishell.h"

static char *find_command(char **paths, char *cmd)
{
    char	*full_path;
	int		i;

	i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], cmd);
        if (access(full_path, F_OK | X_OK) == 0)
		{
			printf("find command : %s\n", full_path);
            return (full_path);
		}
        free(full_path);
        i++;
    }
	printf("WTF\n");
    return (NULL);
}

static char **split_path(char *path)
{
    char **paths;
	char *tmp;
    int i;

	paths = ft_split(path, ':');
	if (!paths)
        return (NULL);
	tmp = NULL;
	i = 0;
    while (paths[i])
    {
        tmp = paths[i];
        paths[i] = ft_strjoin(tmp, "/");
		printf("in split path : path = %s", paths[i]);
        free(tmp);
        i++;
    }
    return (paths);
}

static int check_and_set_path(t_input_data *data)
{
    char **paths;
    char *command_path;
    //int i;

    /*if (!data->path) {
        // PATH n'est pas défini, vérifiez si la commande est un chemin absolu
        if (data->data[0] == '/' && access(data->data, F_OK | X_OK) == 0) {
            data->path = ft_strdup(data->data);
            return (data->path == NULL) ? 1 : 0;
        }
        return 1;
    }*/
	printf("--- in check_and_set path\n");
    paths = split_path(data->path);
    if (!paths)
        return (1);

    command_path = find_command(paths, data->data);
	printf("--- command path = %s\n", command_path);
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
		printf("path = %s\n", data->path);
    }
	else
	{
        return (1);
    }
    return (0);
}

static int get_path(t_exec *ex, t_input_data *data)
{
    //char	*path;
    int		i;

    printf("--- IN GET PATH\n");
    if (ex->env == NULL || *ex->env == NULL)
        return (1);
	i = 0;
    while (ex->env[i])
    {
        if (ft_strncmp(ex->env[i], "PATH=", 5) == 0)
        {
            data->path = ft_strdup(ex->env[i] + 5);
			printf("--- path = %s\n", data->path);
            break;
        }
        i++;
    }
	//printf("in get path : %s\n", data->path);
    return (0);
}

int make_path(t_exec *ex, t_input_data *data)
{
    t_input_data *current;
	
	current = data;
	if (data->path)
		free(data->path);
    printf("--- IN_MAKE_PATH\n");
    if (get_path(ex, data) == 1)
        return (1);
    while (current)
    {
        if (current->cmd_type == 1)
        {
            if (check_and_set_path(current) == 1)
                return (1);
        }
        current = current->next;//next_data_same_command_id
    }
    return (0);
}

int	make_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
