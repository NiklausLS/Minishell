/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:23:16 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/06 08:05:28 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void    print_error(int error, char *cmd)
{
    if (error == 0)
    {
        ft_putstr_fd("Minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    }
    else if (error == 1)
    {
        ft_putstr_fd("Minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": command not found\n", 2);
    }
    else if (error == 2)
    {
        ft_putstr_fd("Minishell: ", 2);
        ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
    }
}