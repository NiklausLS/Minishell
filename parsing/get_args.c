/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:02:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 16:20:38 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

/*void    get_args(char *test, t_data *data)
{
    data->args = ft_split(*argv, ' ');
}*/

static void parse_redirection(t_commands *current)
{
    int redir_type;

    redir_type = check_redirection(current->cmd);
    if (redir_type == 0 || redir_type == 1)
        current->input_type = redir_type;
    else if (redir_type == 2 || redir_type == 3)
    {
        current->output = ft_strdup(current->cmd);
        current->output_type = redir_type;
    }
    current->cmd = NULL;
}

static void parse_pipe(t_commands *current)
{ 
    if (current->cmd)
    {
        current->pipe_type = 1;
        printf("%s is a pipe\n", current->cmd);
    }
}

/*static void parse_command(t_commands *current, t_commands *previous)
{
    if (previous && previous->cmd && previous->cmd[0] != '|' &&
        !previous->input && !previous->output)
    {
        current->cmd = NULL;
    }
}*/

void    check_lst(t_data *data)
{
    t_commands  *current;
    //t_commands  *previous;
    int         i;

    current = data->cmd_lst;
    i = 0;
    while (current)
    {
        printf("check cmd %d : %s\n", i, current->cmd);
        if (check_redirection(current->cmd) != -1)
            parse_redirection(current);
        else if (check_pipe(current->cmd) == 0)
            parse_pipe(current);
        else
        {
            printf("%s is a cmd\n", current->cmd);
        }
        current = current->next;
        i++;
    }
    printf("----------------------\n");
}