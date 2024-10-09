/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:30:35 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 23:17:40 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*make_new_var(char *var, char *sign, size_t var_len, size_t len)
{
	char	*new_var;

	new_var = (char *)malloc(var_len + len + 4);
	if (new_var)
	{
		ft_memcpy(new_var, var, var_len + 1);
		new_var[var_len + 1] = '"';
		ft_strcpy(new_var + var_len + 2, sign + 1);
		new_var[var_len + len + 2] = '"';
		new_var[var_len + len + 3] = '\0';
	}
	return (new_var);
}

char	*make_quotes(char *var)
{
	char	*sign;
	size_t	var_len;
	size_t	len;
	char	*new_var;

	sign = ft_strchr(var, '=');
	if (!sign)
	{
		sign = ft_strdup(var);
		return (sign);
	}
	if (*(sign + 1) == '\0')
	{
		new_var = ft_strdup(var);
		return (new_var);
	}
	var_len = sign - var;
	len = ft_strlen_ptr(sign + 1);
	if (sign[1] == '"' && sign[len] == '"')
	{
		new_var = ft_strdup(var);
		return (new_var);
	}
	new_var = make_new_var(var, sign, var_len, len);
	return (new_var);
}

int	update_env_loop(t_exec *ex, char **up_env, char *quote_var, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		up_env[j] = ex->env[j];
		j++;
	}
	up_env[i] = ft_strdup(quote_var);
	if (!up_env[i])
	{
		while (--j >= 0)
			free(up_env[j]);
		return (1);
	}
	up_env[i + 1] = NULL;
	free(ex->env);
	ex->env = up_env;
	return (0);
}
