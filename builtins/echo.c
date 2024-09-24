/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:37:56 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/24 19:06:19 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_echo(t_token *data)
{
	int	new_line;
	int	i;

	new_line = 1;
	parse_args(data);
	if (data->args[1])
		printf("data->args[1] = %s\n", data->args[1]);
	if (data->args[1])
	{
		i = 1;
		while (ft_strcmp(data->args[i], "-n") == 0)
		{
			new_line = 0;
			i++;
		}
		while (data->args[i])
		{
			printf("%s", data->args[i]);
			if (data->args[i + 1])
				printf(" ");
			i++;
		}
		if (new_line)
			printf("\n");
	}
}
