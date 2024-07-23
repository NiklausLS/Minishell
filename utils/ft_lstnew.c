/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/23 19:04:51 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ajoute à une node commande des arguments
void	add_arg(t_token *data)
{
	t_token	*current;
	t_token	*last;
	int			i;

    printf("-- in add_arg\n");
	/*if (!data || data->cmd_lst)
		return ;*/
	last = NULL;
    current = data;
	while (current)
	{
        printf("in current loop\n");
        if (current->type == COMMAND)
        {
            last = current;
            printf("last command is %s\n", last->args[0]);
        }
		if (current->type == COMMAND && current != last)
		{
			i = 0;
            printf("-- %s is an arg\n", current->value);
			while (last->args[i])
				i++;
			last->args[i] =  ft_strdup(current->value);
			last->args[i + 1] = NULL;
 		}
		current = current->next;
	}
    //print_array(current->args);
}

/*
 * Print the env for checks
 */
int	make_env(char **envp)
{
	int	i;

	i = 0;
    if (!envp)
	{
        return (1);
	}
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}