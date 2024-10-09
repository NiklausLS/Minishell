/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 20:56:41 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	without_args(t_exec *ex)
{
	int		i;
	char	**tab_ptr;
	int		count;

	i = 0;
	count = 0;
	while (ex->env[count])
		count++;
	tab_ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab_ptr)
		return ;
	while (i < count)
	{
		tab_ptr[i] = ex->env[i];
		i++;
	}
	tab_ptr[i] = NULL;
	sort_ex(tab_ptr, count);
	print_export(tab_ptr, count);
	free(tab_ptr);
}

static int	get_index(t_exec *ex, char *var)
{
	int			i;
	size_t		len;
	char		*check_sign;

	i = 0;
	check_sign = ft_strchr(var, '=');
	if (check_sign)
		len = check_sign - var;
	else
		len = ft_strlen(var);
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], var, len) == 0 && ex->env[i][len] == '=')
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

static int	make_update_env(t_exec *ex, char *var)
{
	int		index;
	char	*new_var;

	new_var = make_quotes(var);
	if (!new_var)
		return (1);
	index = get_index(ex, var);
	if (index != -1)
	{
		free(ex->env[index]);
		ex->env[index] = new_var;
	}
	else
	{
		index = 0;
		while (ex->env[index])
			index++;
		index--;
		ex->env = custom_realloc(ex->env, index + 1, index + 2);
		ex->env[index + 1] = new_var;
		ex->env[index + 2] = NULL;
	}
	return (0);
}

int	make_export(t_token *data, t_exec *ex)
{
	if (!data->next)
	{
		without_args(ex);
		return (0);
	}
	while (data->next)
	{
		if (ft_strchr(data->next->value, '=')
			|| get_index(ex, data->next->value) != -1)
			make_update_env(ex, data->next->value);
		data = data->next;
	}
	return (0);
}
