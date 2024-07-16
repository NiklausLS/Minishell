/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:57:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/16 20:57:58 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_args(t_input_data *data)
{
	t_input_data	*current;
    int			count;
	int			i;

	count = 0;
	//current = NULL;
	//printf("in parse_args");
	if (!data->data)
		return (1);
	current = data;
	//printf("in parse_args\n");
	//printf("cmd = %s\n", current->data);
	data->args = ft_split(data->data, ' ');
	//printf("current args = %s\n", current->args[0]);
	if (data->next)
	{
		current = data->next;
		//printf("next->cmd = %s\n", data->next->data);
	}
	while (current && current->arg_type == 1 && current->pipe_type == -1)
	{
		count++;
		//printf("%s is an arg_type\n", current->data);
		current = current->next;
	}
	data->args = malloc(sizeof(char *) * (count + 2));
	if (!data->args)
		return (1);
	data->args[0] = ft_strdup(data->data);
	i = 1;
	if (data->next)
		current = data->next;
	while (i <= count)
	{
		data->args[i] = ft_strdup(current->data);
		//printf("cmd->args[%d] = %s\n", i, data->args[i]);
		current = current->next;
		i++;
	}
	data->args[i] = NULL;
	return (0);
}

/*static void    get_cmd_args(t_commands *cmd)
{
    int	count;
	int	i;
	t_commands *arg;

	count = count_args(cmd);
	printf("in get_cmd_args : count = %d\n", count);
	cmd->args = malloc((count + 2) * sizeof(char *));
	if (cmd->args == NULL)
		return ;
	i = 1;
	arg = cmd->next;
	while (i <= count)
	{
		cmd->args[i] = ft_strdup(arg->cmd);
		printf("cmd->args[%d] = %s\n", i, cmd->args[i]);
		i++;
		arg = arg->next;
	}
	cmd->args[i] =  NULL;
}*/

/*static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}*/

/*void parse_args(t_commands *cmd)
{
	t_commands	*current;
	int		i;
	int		arg;
	
	printf("in parse_args\n");
	if (cmd->cmd_type != 1 || !cmd->next)
		return ;
	printf("%s is a cmd_type\n", cmd->cmd);
	size = 0;
	while (cmd->args && cmd->args[size])
		size++;
	new_args = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return ;
	new_args[0] = ft_strdup(cmd->cmd);
	i = 0;
	while (i < size)
	{
		new_args[i + 1] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_args[size + 1] = NULL;
	if (cmd->args)
		free_args(cmd->args);
	cmd->args = new_args;
	i = 0;
	//print_array(&cmd->args[i]);
}

void	parse_args(t_commands *cmd)
{
	t_commands	*current;
	//int			i;

	current = cmd;
	//i = 0;
	printf("in parse_args\n");
	if (current->cmd_type == 1)
	{
		printf("current->cmd = %s\n", current->cmd);
		get_cmd_args(current);
	}
	if (current->pipe_type == 1)
		current = current->next;
	else
		current = current->next;
}*/
