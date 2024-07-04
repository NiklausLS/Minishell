/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:02:33 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/04 20:00:11 by nileempo         ###   ########.fr       */
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
    printf("- IN_PARSE_redirection\n");
    printf("-- redir_type = %d\n", redir_type);
    if (redir_type == 0 || redir_type == 1)
    {
        current->input_type = redir_type;
        current->input = ft_strdup(current->next->cmd);
        printf("--- current->input = %s\n", current->output);
        current->cmd_type = -1;
        printf("--- current->input_type = %d\n", current->input_type);
    }
    else if (redir_type == 2 || redir_type == 3)
    {
        current->output_type = redir_type;
        current->output = ft_strdup(current->next->cmd);
        printf("--- current->output = %s\n", current->output);
        current->next->file_type = 1;
        current->cmd_type = -1;
        printf("--- current->output_type = %d\n\n", current->output_type);
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
    t_commands  *current_errors;
    //t_commands  *previous;
    int         i;

    current = data->cmd_lst;
    current_errors = data->cmd_lst;
    i = 0;
    while (current)
    {
        printf("IN check_lst %d : %s\n", i, current->cmd);
        //if (check_redirection(current->cmd) != -1)
        parse_redirection(current);
        if (check_pipe(current->cmd) == 0)
            parse_pipe(current);
        else
        {
            if (current->file_type == -1 && current->input_type == -1
                && current->output_type == -1)
                current->cmd_type = 1;
        }
        /*printf("cmd = %s\n", current->args[0]);
		printf("input_type = %d && input = %s\n", current->input_type, current->input);
		printf("out_type = %d && output = %s\n", current->output_type, current->output);
		printf("cmd_type = %d\n", current->cmd_type);
		printf("file_type = %d\n", current->file_type);
		printf("pipe_tye = %d\n", current->pipe_type);*/
        current = current->next;
        i++;
        printf("        ----\n");
    }
    while (current_errors)
    {
        pipe_errors(current_errors);
        current_errors = current_errors->next;
    }
    printf("----------------------\n");
}