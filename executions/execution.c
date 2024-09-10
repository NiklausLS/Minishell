/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:41:36 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/10 19:04:19 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Find the position of the next command
 */
t_token	*find_command(t_token *start, t_token *end)
{
	t_token	*cmd;

	cmd = start;
	while (cmd != end && cmd->type != COMMAND)
		cmd = cmd->next;
	return (cmd);
}

/*
 * find the position of the next command
 */
t_token	*get_command_end(t_token *start)
{
	t_token	*cmd;

	cmd = start;
	while (cmd && cmd->next)
	{
		if (cmd->next->type == PIPE)
			return (cmd);
		if (cmd->next->type == COMMAND)
			return (cmd);
		cmd = cmd->next;
	}
	//printf("- in find_command_end : cmd is %s\n", cmd->value);
	return (cmd);
}

/*
 * Make a process for each node and use a function depending of the type of the token inside
 */
int	make_child(t_token *start, t_exec *ex)
{
	pid_t	pid;

	pid = fork();
	//printf("---- in make_child : start = %s end = %s\n",
	//	start->value, end->value);
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork error\n", 2);
		return (1);
	}
	else if (pid == 0)
	{
		setup_in_and_out(ex);
		if (get_builtin(start) == 0)
			make_builtin(start, ex);
		else
		{
			//printf("*** --- before make_execve\n");
			make_execve(start, ex);
			exit(127);
		}
		exit (0);
	}
	return (0);
}
static char **prepare_args(t_token *data)
{
    char **args;
    int i;
    t_token *current;

    i = 0;
    current = data;
    while (current && current->type != PIPE)
    {
        current = current->next;
		i++;
    }
    args = (char **)malloc(sizeof(char *) * (i + 1));
    if (!args)
        return (NULL);
    i = 0;
    current = data;
    while (current && current->type != PIPE)
    {
        args[i++] = ft_strdup(current->value);
        current = current->next;
    }
    args[i] = NULL;
    return (args);
}

int make_execve(t_token *data, t_exec *ex)
{
    make_path(ex, data);
    if (data->path == NULL)
    {
        print_error(1, data->value);
        exit(1);
    }
    if (!data->args)
        data->args = prepare_args(data);
    if (!data->args)
    {
        print_error(1, "Memory allocation failed");
        exit(1);
    }
    if (execve(data->path, data->args, ex->env) == -1)
        exit(127);
    return (0);
}
