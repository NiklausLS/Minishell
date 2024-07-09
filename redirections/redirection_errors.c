/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:19:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/09 13:22:21 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_errors(t_input_data *data)
{
	if (data->pipe_type == 1)
	{
		if (data->next_data_same_command_id->pipe_type == 1)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	if (data->input_type != -1 || data->output_type != -1)
	{
		if (data->next_data_same_command_id->pipe_type == 1)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	redirection_errors(t_input_data *data)
{
	//printf("in redirection_errors\n");
	//print_node(cmd);
	if (data->input_type == 1 || data->output_type)
	{
		/*if (cmd->next == )
		{
			printf("test\n");
			print_error(2, "");
			exit(EXIT_FAILURE);
		}*/
		//printf("should work\n");
	}
}
