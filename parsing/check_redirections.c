/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:53:39 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/03 15:01:52 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Check if there is a redirection token and return a value depending of it
 * return -1 if nothing is found
 */
int	check_redirection(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str && str[i])
	{
		if (str[i] == '<')
		{
			if (str[i] == '<' && str[i + 1] == '<')
				return (1);
			else
				return (0);
		}
		else if (str[i] == '>')
		{
			if (str[i] == '>' && str[i + 1] == '>')
				return (3);
			else
				return (2);
		}
		i++;
	}
	return (-1);
}

/*
 * Check if there is a pipe in the node
 */
int	check_pipe(char *str)
{
	if (str == NULL)
		return (-1);
	if (str[0] == '|')
		return (0);
	return (-1);
}

int	check_last_node(t_token *data)
{
	t_token	*current;

	current = data;
	while (current && current->next != NULL)
	{
		printf("current = %s\n", current->value);
		current = current->next;
	}
	printf("current = %s\n", current->value);
	if (!ft_strcmp(current->value, "<") || !ft_strcmp(current->value, "<<") || !ft_strcmp(current->value, ">") || !ft_strcmp(current->value, ">>"))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
