/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/21 15:29:25 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

t_data	*ft_lstnew(char **args)
{
    t_data  *new;

    new = (t_data*)malloc(sizeof(t_data));
    new->args = args;
	new->fd = 0;
	new->path = NULL;
	new->env = NULL;
    new->next = NULL;
    return (new);
}

void	ft_addlst(char **args, t_data **head)
{
	t_data	*new;
	t_data	*current;

	new = ft_lstnew(args);
	current = NULL;
	if (*head == NULL)
	{
		printf("head = NULL\n");
		*head = ft_lstnew(args);
	}
	else
	{
		printf("head != NULL\n");
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}