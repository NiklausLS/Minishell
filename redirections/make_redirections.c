/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:17:53 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/26 01:19:45 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static int dup_output(int fd);
static int dup_input(int fd);

/*
 * check if there is a input or an output and open it
 */
static int redirections(t_token *current, int *last_input, int *last_output)
{
    if (current->type == INPUT || current->type == HEREDOC)
    {
        if (*last_input != -1)
        {
            if (protected_close(*last_input) == 1)
                return (1);
        }
        *last_input = open_input(current);
        if (*last_input == -1)
            return (1);
    }
    if (current->type == OUTPUT || current->type == APPEND)
    {
        if (*last_output != -1)
        {
            if (protected_close(*last_output) == 1)
                return (1);
        }
        *last_output = open_output(current);
        if (*last_output == -1)
            return (1);
    }
    return (0);
}

int make_all_redirections(t_token *start, t_token *end)
{
    t_token *current;
    int     last_input;
    int     last_output;

    //printf("IN make_all_redirections\n");
    current = start;
    last_input = -1;
    last_output = -1;
    while (current && current != end)
    {
        //printf("value : %s type: %d\n", current->value, current->type);
        if (redirections(current, &last_input, &last_output) == 1)
            return (1);
        current = current->next;
    }
    //printf("BEFORE dup_input\n");
    if (last_input == -1 && last_output == -1)
        return (0);
    if (dup_input(last_input) == 1)
        return (1);
    //printf("AFTER dup_input\n");
    if (dup_output(last_output) == 1)
        return (1);

    if (last_input != -1)
    {
        //printf("last_input  %d\n", last_input);
        close (last_input);
        //printf("last_input  %d\n", last_input);
    }
    if (last_output != -1)
    {
        //printf("last_output %d\n", last_output);
        close (last_output);
        //printf("last_output %d\n", last_output);
    }
    //printf("END make_all_redirections\n");
    return (0);
}

static int dup_input(int fd)
{
    //printf("IN dup_input with fd=%d\n", fd);
    if (fd != -1)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            close(fd);
            return (1);
        }
        //printf("dup2 for input OK\n");
        close(fd);
    }
    return (0);
}

static int dup_output(int fd)
{
    //printf("IN dup_output fd = %d\n", fd);
    if (fd != -1)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            ft_putstr_fd("Minishell: dup2 error\n", 2);
            //close(fd);
            return (1);
        }
        //printf("dup2 for output OK\n");
        close(fd);
    }
    //printf("END dup_output fd = %d\n", fd);
    return (0);
}

t_token *get_end(t_token *start)
{
    t_token *current;
    
    current = start;
    //printf("in get_end\n");
    while (current != NULL && current->type != PIPE && current->next)
    {
        //printf("data = %s\n", current->value);
        current = current->next;
    }
    //printf("end is %s\n", current->value);
    return (current);
}
