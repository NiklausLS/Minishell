/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:26:09 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 22:26:24 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_index(t_exec *ex, char *var)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (ex->env[i])
	{
		if (ft_strncmp(ex->env[i], var, size) == 0 && ex->env[i][size] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	delete_var(t_exec *ex, int index)
{
	free(ex->env[index]);
	ex->env[index] = NULL;
	while (ex->env[index + 1])
	{
		ex->env[index] = ex->env[index + 1];
		index++;
	}
	ex->env[index] = NULL;
}

int	make_unset(t_token *data, t_exec *ex)
{
	int	index;

	if (data->next == NULL)
		return (1);
	index = get_index(ex, data->next->value);
	if (index != -1)
		delete_var(ex, index);
	return (0);
}
