/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:23:16 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/10 05:10:30 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Will print an error message depending of the int it gets
 */
int	print_error(int error, char *cmd)
{
	ft_putstr_fd("Minishell: ", 2);
	if (error == 5)
		ft_putstr_fd("cd: ", 2);
	if (error != 2 && error != 6)
		ft_putstr_fd(cmd, 2);
	if (error == 0 || error == 5)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (error == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (error == 2)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	else if (error == 3)
		ft_putstr_fd(": permission denied\n", 2);
	else if (error == 4)
		ft_putstr_fd(": not a directory\n", 2);
	else if (error == 6)
		ft_putstr_fd("Failed to initialize exec structure\n", 2);
	return (1);
}

/*
 * Will print what is in the node if there is something to check
 * if i'm not a complete donkey
 */
void	print_node(t_token *data)
{
	t_token	*current;
	int		i;

	current = data;
	i = 0;
	printf("---print node---\n");
	if (current->value)
		printf("- cmd = %s\n", current->value);
	if (current->type)
		printf("- type = %d\n", current->type);
	if (current->path)
		printf("path = %s\n", data->path);
	while (data->args[i])
	{
		printf("arg[%d] = %s\n", i, data->args[i]);
		i++;
	}
}

void	print_env(t_exec *ex)
{
	int	i;

	i = 0;
	while (ex->env[i])
	{
		printf("%s\n", ex->env[i]);
		i++;
	}
}
