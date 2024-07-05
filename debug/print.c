/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 07:21:27 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 15:17:49 by nileempo         ###   ########.fr       */
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

void	print_linked_list(t_data *data)
{
	t_commands	*current;
	int		i;

	current = data->cmd_lst;
	while (current)
	{
		i = 0;
		//printf ("cmd = ");
		if (current->args)
		{
			while (current->args[i])
			{
				printf ("cmd = ");
				printf("current->args[%d] = %s\n", i, current->args[i]);
				i++;
			}
		}
		else
			printf("%s", current->cmd);
		printf("\n");
		current = current->next;
	}
}

void	print_node(t_commands *cmd)
{
	int	i;

	i = 0;
	printf("---child---\n");
	printf("cmd = ");
	if (cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
	if (cmd->input_type != -1)
		printf("input_type = %d && input = %s\n", cmd->input_type, cmd->input);
	if (cmd->output_type != -1)
		printf("out_type = %d && output = %s\n", cmd->output_type, cmd->output);
	if (cmd->cmd_type != -1)
		printf("cmd_type = %d\n", cmd->cmd_type);
	if (cmd->file_type != -1)
		printf("file_type = %d\n", cmd->file_type);
	if (cmd->pipe_type != -1)
		printf("pipe_type = %d\n", cmd->pipe_type);
	printf("---child end---\n");
}