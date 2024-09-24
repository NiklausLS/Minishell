/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:06:54 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/24 19:03:24 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_ex(char **env, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

void	print_export(char **env, int count)
{
	char	*new_var;
	int		i;

	i = 0;
	while (i < count)
	{
		new_var = make_quotes(env[i]);
		if (new_var)
		{
			printf("declare -x %s\n", new_var);
			free(new_var);
		}
		i++;
	}
}
