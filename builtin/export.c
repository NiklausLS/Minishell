/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/07 22:32:54 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//done
//export without args

//to do list
//with args
//change path
//export with bad syntax
//change une variable en variable d'env

//ne doit pas faire sortir de var d'en de env (c'est l'option -n et pas à gérer)

//should return 0 if succes
//anything else if error

static void without_args(t_exec *ex)
{
    int i;

    i = 1;
    while (ex->env[i])
    {
        printf("declare -x %s\n", ex->env[i]);
        i++;
    }
}

static int  get_index(char **env, char *var)
{
    int     i;
    size_t  len;
    char    *check_sign;

    i = 0;
    check_sign = ft_strchr(var, '=');
    printf("var = %s\n", var);
    if (check_sign)
        len = check_sign - var;
    else
		len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{
			printf("var found at index %d\n", i);
			return (0);
		}
		i++;
	}
	printf("var not found\n");
	return (-1);
}

static void	update_env(t_exec *ex, int index, char *var)
{
	int		i;
	char	**up_env;
	int		j;

	printf("in update_env\n");
	i = 0;
	j = 0;
	if (index != -1)
	{
		free(ex->env[index]);
		ex->env[index] = ft_strdup(var);
	}
	else
	{
		while (ex->env[i])
			i++;
		up_env = (char **)malloc(sizeof(char *) * (i + 2));
		if (up_env)
		{
			while (j < i)
			{
				up_env[j] = ex->env[j];
				j++;
			}
			up_env[i] = ft_strdup(var);
			up_env[i + 1] = NULL;
			free(ex->env);
			ex->env = up_env;
		}
	}
}

static void	make_update_env(t_exec *ex, char *var)
{
	int	index;

	printf("adding %s\n", var);
	index = get_index(ex->env, var);
	update_env(ex, index, var);
}

int make_export(t_commands *cmd, t_exec *ex)
{
    if (!cmd->next)
	{
        without_args(ex);
		return (0);
	}
	while (cmd->next)
	{
		printf("checking arg = %s\n", cmd->cmd);
		if (ft_strchr(cmd->cmd, '=') || get_index(ex->env, cmd->next->cmd) != -1)
			make_update_env(ex, cmd->next->cmd);
		cmd = cmd->next;
	}
	return (0);
}