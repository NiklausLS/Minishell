/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:25:10 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/09 20:58:56 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * check if there is something behind the pipe and send error according to it
 */
/*int	pipe_errors(t_token *data)
{
	if (!data)
	{
		ft_putstr_fd("Error, no data\n", 2);
		return (1);
	}
	if (!data->next)
	{
		//ft_putstr_fd("No data->next\n", 2);
		return (0);
	}
	if (data->pipe_type == 1)
	{
		if (data->next->pipe_type == 1 && data->quotes == 0)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	if ((data->input_type != -1 || data->output_type != -1) && data->quotes == 0)
	{
		if (data->next->pipe_type == 1)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
    return (0);
}*/
