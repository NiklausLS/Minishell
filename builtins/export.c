/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/27 00:13:46 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	without_args(t_exec *ex)
{
	int		i;
	char	**tab_ptr;
	int		count;

	i = 0;
	count = 0;
	while (ex->env[count])
		count++;
	tab_ptr = (char **)malloc(sizeof(char *) * count);
	if (!tab_ptr)
		return ;
	while (i < count)
	{
		tab_ptr[i] = ex->env[i];
		i++;
	}
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

static int	update_env(t_exec *ex, int index, char *var)
{
	int		i;
	char	**up_env;
	char	*quote_var;

	i = 0;
	quote_var = make_quotes(var);
	if (!quote_var)
		return (1);
	if (index != -1)
	{
		free(ex->env[index]);
		ex->env[index] = ft_strdup(var);
		if (!ex->env[index])
		{
			free(quote_var);
			return (1);
		}
	}
	else
	{
		i = 0;
		while (ex->env[i])
			i++;
		up_env = (char **)malloc(sizeof(char *) * (i + 2));
		if (!up_env)
		{
			free(quote_var);
			return (1);
		}
		if (update_env_loop(ex, up_env, quote_var, i) != 0)
		{
			free(up_env);
			free(quote_var);
			return (1);
		}
	}
	free(quote_var);
	return (0);
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
		if (update_env(ex, index, var) != 0)
		{
			free(new_var);
			return (1);
		}
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
