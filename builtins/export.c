/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/27 16:37:17 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	without_args(t_exec *ex)
{
	int		i;
	//char	*new_var;
	char	**tab_ptr;
	int		count;

	i = 0;
	count = 0;
	printf("in without args\n");
	while (ex->env[count])
		count++;	
	tab_ptr = (char **)malloc(sizeof(char *) * count);
	if (!tab_ptr)
		return ;
	while (i < count)
	{
		tab_ptr[i] =  ex->env[i];
		i++;
	}
	printf("fin de without args\n");
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
	printf("var = %s\n", var);
	printf("check_sign = %s\n", check_sign);
	printf("var = %s\n", var);
	if (check_sign)
	{
		len = check_sign - var;
		printf("len = %zu\n", len);
	}
	else
	{
		len = ft_strlen(var);
		printf("else len = %zu\n", len);
	}
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], var, len) == 0 && ex->env[i][len] == '=')
		{
			printf("var index %d\n", i);
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	update_env(t_exec *ex, int index, char *var)
{
	int		i;
	char	**up_env;
	char	*quote_var;

	printf("*** in update_env\n");
	i = 0;
	quote_var = make_quotes(var);
	if (!quote_var)
		return (1);
	if (index != -1)
	{
		free(ex->env[index]);
		printf("** freeing enx->env[%d] : %s\n", index, ex->env[index]);
		ex->env[index] = ft_strdup(var);
		printf("** copy var %s\n", var);
		if (!ex->env[index])
		{
			free(quote_var);
			return (1);
		}
	}
	else
	{
		printf("** var not found so index == -1\n");
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
	printf("--- in make_update_env\n");
	printf("-- adding %s\n", var);
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
	//printf("- index = %d\n", index);
	//printf("calling update_env\n");
	return (0);
}

int	make_export(t_token *data, t_exec *ex)
{
	if (!data->next)
	{
		printf("NO ARGUMENTS\n");
		without_args(ex);
		return (0);
	}
	printf("cmd->cmd = %s\n", data->value);
	while (data->next)
	{
		printf("checking arg = %s\n", data->next->value);
		if (ft_strchr(data->next->value, '=')
			|| get_index(ex, data->next->value) != -1)
			make_update_env(ex, data->next->value);
		data = data->next;
	}
	return (0);
}
