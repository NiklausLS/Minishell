/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:41:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 05:23:40 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_in_env(char *to_find, char **env)
{
	int	len;
	int	i;

	len = ft_strlen(to_find);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	update_env_value(t_exec *ex, char *name, char *value)
{
	int	i;

	i = find_in_env(name, ex->env);
	if (i >= 0)
	{
		free(ex->env[i]);
		ex->env[i] = ft_strjoin(name, value);
		return ;
	}
	i = 0;
	while (ex->env[i])
		i++;
	i--;
	ex->env = custom_realloc(ex->env, i + 1, i + 2);
	ex->env[i + 1] = ft_strjoin(name, value);
	ex->env[i + 2] = NULL;
}

static int	cd_prev(t_exec *ex, t_token *data)
{
	if (find_in_env("OLDPWD=", ex->env) < 0)
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		free_array(data->args);
		return (1);
	}
	ft_putendl_fd(ex->env[find_in_env("OLDPWD=", ex->env)] + 7, 2);
	chdir(ex->env[find_in_env("OLDPWD=", ex->env)] + 7);
	free_array(data->args);
	return (0);
}

static int	cd_with_arg(t_exec *ex, t_token *data, char *oldpwd)
{
	char	*tmp;

	if (ft_strcmp(data->args[1], "-") == 0)
		return (cd_prev(ex, data));
	else if (chdir(data->args[1]))
	{
		print_error(5, data->args[1]);
		free_array(data->args);
		return (1);
	}
	else
	{
		tmp = getcwd(NULL, 0);
		update_env_value(ex, "OLDPWD=", oldpwd);
		update_env_value(ex, "PWD=", tmp);
		free(tmp);
	}
	free_array(data->args);
	return (0);
}

int	make_cd(t_exec *ex, t_token *data)
{
	char	*oldpwd;

	parse_args(data);
	oldpwd = (ex->env[find_in_env("PWD=", ex->env)] + 4);
	if (data->args[1])
		return (cd_with_arg(ex, data, oldpwd));
	else if (!data->args[1])
		chdir(ex->env[find_in_env("HOME=", ex->env)] + 5);
	else if (data->args[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		free_array(data->args);
		return (1);
	}
	free_array(data->args);
	return (0);
}
