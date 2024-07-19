/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:57:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/19 20:04:30 by nileempo         ###   ########.fr       */
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
	t_token	*current;
    int			count;
	int			i;

	count = 0;
	//current = NULL;
	//printf("in parse_args");
	if (!data->value)
		return (1);
	current = data;
	//printf("in parse_args\n");
	//printf("cmd = %s\n", current->data);
	data->args = ft_split(data->value, ' ');
	//printf("current args = %s\n", current->args[0]);
	if (data->next)
	{
		current = data->next;
		//printf("next->cmd = %s\n", data->next->data);
	}
	while (current && current->type == TEXT && current->type == PIPE)
	{
		count++;
		//printf("%s is an arg_type\n", current->data);
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
		//printf("cmd->args[%d] = %s\n", i, data->args[i]);
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
	//t_token	*current_errors;
	int				first_cmd;
    //int             check_red;

	current = data;
	//current_errors = data;
    first_cmd = 1;
    printf("IN CHECK LST\n");
	/*while (current_errors)
	{
		if (pipe_errors(current_errors) == 1)
            return (1);
		if (redirection_errors(current_errors) == 1)
            return (1);
		current_errors = current_errors->next;
	}*/
    //printf("après current_error\n");
    while (current != NULL)
	{
        //printf("current = %s\n", current->data);
        if (first_cmd == 1)
        {
                current->type = COMMAND;
                first_cmd = 0;
                //print_node(current);
        }
		if ((current->type == INPUT || current->type == HEREDOC
			|| current->type == OUTPUT || current->type == APPEND)
				&& current->next)
				current->next->type = FI;
		if (current->type == PIPE && current->next)
			current->next->type = COMMAND;
		print_node(current);
        current = current->next;  
    }
    return (0);
}