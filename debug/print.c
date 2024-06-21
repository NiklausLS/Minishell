/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 07:21:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/21 09:19:56 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array[%d] = %s\n", i, array[i]);
		i++;
	}
}

void	print_linked_list(t_data *head)
{
	t_data	*current;
	int		i;

	current = head;
	while (current)
	{
		i = 0;
		printf ("cmd = ");
		while (current->args[i])
		{
			printf("%s ", current->args[i]);
			i++;
		}
		printf("\n");
		current = current->next;
	}
}
