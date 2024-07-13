/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:23:16 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/13 19:15:52 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(int error, char *cmd)
{
	ft_putstr_fd("Minishell: ", 2);
	if (error == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (error == 2)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (error == 3)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else if (error == 4)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": not a directory\n", 2);
	}
}

void    print_node(t_input_data *data)
{
    t_input_data *current;

    current = data;
    printf("---print node---\n");
    if (current->data)
        printf("- cmd = %s\n", current->data);
    if (current->input_type != -1)
        printf("- input type = %d\n", current->input_type);
    if (current->output_type != -1)
        printf("- output type = %d\n", current->output_type);
    if (current->cmd_type == 1)
        printf("- cmd type = %d\n", current->cmd_type);
    if (current->file_type == 1)
        printf("- file type = %d\n", current->file_type);
    if (current->arg_type == 1)
        printf("- arg type = %d\n", current->arg_type);
    if (current->pipe_type == 1)
        printf("- pipe type = %d\n", current->pipe_type);
}