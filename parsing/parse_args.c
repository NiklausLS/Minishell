/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:57:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/09/25 07:31:16 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Will go through every node until it found a pipe
 * everything who is not a redirection or a pipe will be given a argument type
 * @return : return 0 if everything is ok, 1 if a malloc failed
 */
int	parse_args(t_token *data)
{
	t_token		*current;
	int			count;
	int			i;

	count = 0;
	if (!data->value)
		return (1);
	current = data;
	data->args = ft_split(data->value, ' ');
	if (data->next)
		current = data->next;
	while (current && current->type == TEXT)
	{
		count++;
		current = current->next;
	}
	data->args = malloc(sizeof(char *) * (count + 2));
	if (!data->args)
		return (1);
	data->args[0] = ft_strdup(data->value);
	i = 1;
	if (data->next)
		current = data->next;
	while (i <= count)
	{
		data->args[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	data->args[i] = NULL;
	return (0);
}

/*
 * Will make the first node a command
 * check the rest to give them a type specific to each of them
 * redirection / pipe / argument / command
 * @return 0 if everything is ok, 1 if something is wrong
 * */
int	check_lst(t_token *data)
{
	t_token	*current;
	int				first_cmd;

	current = data;
    first_cmd = 1;
    while (current != NULL)
	{
        if (first_cmd == 1)
        {
			if (current->type != INPUT && current->type != HEREDOC
			&& current->type != OUTPUT && current->type != APPEND)
			{
                current->type = COMMAND;
				//printf("after cmd_type = %d\n", current->type);
                first_cmd = 0;
			}
			first_cmd = 0;
        }
		if ((current->type == INPUT || current->type == HEREDOC
			|| current->type == OUTPUT || current->type == APPEND)
				&& current->next)
		{
				current->next->type = FI;
				//printf("cmd_type = %d\n", current->type);
		}
		if (current->type == PIPE && current->next)
		{
			if (current->next->type != INPUT && current->next->type != HEREDOC
			&& current->next->type != OUTPUT && current->next->type != APPEND)
			{
				current->next->type = COMMAND;
				//printf("cmd_type = %d\n", current->type);
			}
		}
        current = current->next; 
    }
    return (0);
}
