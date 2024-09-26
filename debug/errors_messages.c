/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:23:16 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 15:17:14 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Will print an error message depending of the int it gets
 */
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

/*
 * Will print what is in the node if there is something to check
 * if i'm not a complete donkey
 */
void    print_node(t_token *data)
{
    t_token *current;

    current = data;
    printf("---print node---\n");
    if (current->value)
        printf("- cmd = %s\n", current->value);
    if (current->type)
        printf("- type = %d\n", current->type);
}

void print_env(t_exec *ex)
{
    for (int i = 0; ex->env[i]; i++)
    {
        printf("%s\n", ex->env[i]);
    }
}