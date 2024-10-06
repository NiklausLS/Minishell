/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:41:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/07 00:26:41 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static char	**custom_realloc(char **env, int old_size, int new_size)
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
	while (ex->env[i])
		i++;
	ex->env = custom_realloc(ex->env, i + 1, i + 2);
	ex->env[i] = ft_strjoin(name, value);
	ex->env[i + 1] = NULL;
}

static int	cd_with_arg(t_exec *ex, t_token *data, char *oldpwd)
{
	if (ft_strcmp(data->args[1], "-") == 0)
	{
		if (find_in_env("OLDPWD=", ex->env) < 0)
		{
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		ft_putstr_fd(ex->env[find_in_env("OLDPWD=", ex->env)] + 6, 2);
		ft_putchar_fd('\n', 2);
		chdir(ex->env[find_in_env("OLDPWD=", ex->env)]);
	}
	else if (chdir(data->args[1]))
	{
		print_error(0, ft_strjoin("cd: ", data->args[1]));
		return (1);
	}
	else
	{
		update_env_value(ex, "OLDPWD=", oldpwd);
		update_env_value(ex, "PWD=", getcwd(NULL, 0));
	}
	return (0);
}

int	make_cd(t_exec *ex, t_token *data)
{
	char	*oldpwd;

	parse_args(data);
	oldpwd = (ex->env[find_in_env("PWD=", ex->env)] + 4);
	if (data->args[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (data->args[1])
		return (cd_with_arg(ex, data, oldpwd));
	else if (!data->args[1])
		chdir(ex->env[find_in_env("HOME=", ex->env)] + 5);
	return (0);
}
