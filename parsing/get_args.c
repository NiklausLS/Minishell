/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:02:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 19:09:49 by nileempo         ###   ########.fr       */
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

    //printf("*** IN_PARSE_redirection\n");
    redir_type = check_redirection(current->cmd);
    printf("redir_type = %d\n", redir_type);
    printf("*** IN_PARSE_redirection\n\n");
    if (redir_type == 0 || redir_type == 1)
    {
        current->input_type = redir_type;
        printf("current->input_type = %d\n", current->input_type);
        if (current->next)
        {
            current->next->input = ft_strdup(current->next->cmd);
            printf("current->next->input = %s\n\n", current->next->input);
        }
    }
    else if (redir_type == 2 || redir_type == 3)
    {
        current->next->output = ft_strdup(current->next->cmd);
        printf("current->next->output = %s\n", current->next->output);
        current->output_type = redir_type;
        printf("current->output_type = %d\n\n", current->output_type);
    }
    //current->cmd = NULL;
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
    t_commands  *current_errors;
    //t_commands  *previous;
    int         i;

    current = data->cmd_lst;
    current_errors = data->cmd_lst;
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
    while (current_errors)
    {
        pipe_errors(current_errors);
        current_errors = current_errors->next;
    }
    printf("----------------------\n");
}