/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:02:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/30 07:51:55 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*void    get_args(char *test, t_data *data)
{
    data->args = ft_split(*argv, ' ');
}*/

void    check_lst(t_data *data)
{
    t_commands  *current;
    int         i;

    current = data->cmd_lst;
    i = 0;
    while (current)
    {
        printf("check cmd %d : %s\n", i, current->cmd);
        if (check_redirection(current->cmd) == 0 || check_redirection(current->cmd) == 1)
        {
            printf("Input redirection : %s\n", current->cmd);
            current->input = ft_strdup(current->cmd);
            current->input_type = check_redirection(current->cmd);
        }
        else if (check_redirection(current->cmd) == 2 || check_redirection(current->cmd) == 3)
        {
            printf("Output redirection : %s\n", current->cmd);
            current->output = ft_strdup(current->cmd);
            current->output_type = check_redirection(current->cmd);
        }
        else if (check_pipe(current->cmd) == 0)
        {
            printf("pipe detected\n");
        }
        current = current->next;
        i++;
    }
}