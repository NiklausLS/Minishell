/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:25:47 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/09 15:45:10 by nileempo         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (ex->env[i])
	{
		printf("declare -x %s\n", ex->env[i]);
		i++;
	}
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
		printf("else : len = %zu\n", len);
	}
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], var, len) == 0 && ex->env[i][len] == '=')
		{
			printf("var found at index %d\n", i);
			return (i);
		}
		i++;
	}
	return (-1);
}

static void	update_env(t_exec *ex, int index, char *var)
{
	int		i;
	char	**up_env;
	char	*quote_var;

	printf("*** in update_env\n");
	i = 0;
	quote_var = add_quotes(var);
	if (!quote_var)
		return ;// gestion des erreurs entierement a revoir pour export
	if (index != -1)
	{
		free(ex->env[index]);
		printf("** freeing enx->env[%d] : %s\n", index, ex->env[index]);
		ex->env[index] = ft_strdup(var);
		printf("** copy var %s\n", var);
	}
	else
	{
		printf("** var not found so index == -1\n");
		i = 0;
		while (ex->env[i])
			i++;
		up_env = (char **)malloc(sizeof(char *) * (i + 2));
		if (up_env)
			update_env_loop(ex, up_env, quote_var, i);
		else
			free(quote_var);
	}
}

static void	make_update_env(t_exec *ex, char *var)
{
	int	index;

	printf("--- in make_update_env\n");
	printf("-- adding %s\n", var);
	index = get_index(ex, var);
	printf("- index = %d\n", index);
	printf("calling update_env\n");
	update_env(ex, index, var);
}

int	make_export(t_input_data *data, t_exec *ex)
{
	if (!data->next)
	{
		without_args(ex);
		return (0);
	}
	printf("cmd->cmd = %s\n", data->data);
	while (data->next)
	{
		printf("checking arg = %s\n", data->next->data);
		if (ft_strchr(data->next->data, '=')
			|| get_index(ex, data->next->data) != -1)
			make_update_env(ex, data->next->data);
		data = data->next;
	}
	return (0);
}
