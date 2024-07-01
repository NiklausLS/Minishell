/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:19:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 17:34:32 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void    pipe_errors(t_commands *cmd)
{
    if (cmd->pipe_type == 1)
    {
        if (cmd->next->pipe_type == 1)
        {
            ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
            exit(EXIT_FAILURE);
        }
    }
    if (cmd->input_type != -1  || cmd->output_type != -1)
    {
        if (cmd->next->pipe_type == 1)
        {
            ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
            exit(EXIT_FAILURE);
        }
    }
}