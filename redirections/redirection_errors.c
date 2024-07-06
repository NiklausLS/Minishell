/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:19:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/06 15:11:11 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void	pipe_errors(t_commands *cmd)
{
	if (cmd->pipe_type == 1)
	{
		if (cmd->next->pipe_type == 1)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->input_type != -1 || cmd->output_type != -1)
	{
		if (cmd->next->pipe_type == 1)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	redirection_errors(t_commands *cmd)
{
	//printf("in redirection_errors\n");
	//print_node(cmd);
	if (cmd->input_type == 1 || cmd->output_type)
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
