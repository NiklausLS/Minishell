/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/11 20:39:18 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Pour tester en attendant d'avoir le code du mate

t_input_data *init_node(char *data)
{
    t_input_data *new_node;
    
    new_node = (t_input_data *)malloc(sizeof(t_input_data));
    new_node->data = ft_strdup(data);
    //printf("init_node = data = %s\n", data);
    new_node->args = ft_split(data, ' ');
    printf("--- create node args[0] = %s\n", new_node->args[0]);
    int i = 1;
    while (new_node->args[i])
    {
        printf("--- create node args[%d] : %s\n", i, new_node->args[i]);
        i++;
    }
    new_node->path = NULL;
    //new_node->env = NULL;
    new_node->input_type = -1;
    new_node->input = NULL;
    new_node->output_type = -1;
    new_node->output = NULL;
    new_node->heredoc_delim = NULL;
    new_node->next = NULL;
    new_node->pipe_type = -1;
    new_node->file_type = -1;
    new_node->cmd_type = -1;
    new_node->exec_fail = -1;
    new_node->error = 0;
    new_node->arg_type = -1;
    printf("MAKING A NEW NODE\n");
    return (new_node);
}

// Fonction pour ajouter une node à la fin de la liste
void add_node(t_input_data **head, t_input_data *new_node)
{
    t_input_data *current;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

//ajoute à une node commande des arguments
void	add_arg(t_input_data *data)
{
	t_input_data	*current;
	t_input_data	*last;
	int			i;

    printf("-- in add_arg\n");
	/*if (!data || data->cmd_lst)
		return ;*/
	last = NULL;
    current = data;
	while (current)
	{
        printf("in current loop\n");
        if (current->cmd_type == 1)
        {
            last = current;
            printf("last command is %s\n", last->args[0]);
        }
		if (current->arg_type == 1 && current != last)
		{
			i = 0;
            printf("-- %s is an arg\n", current->data);
			while (last->args[i])
				i++;
			last->args[i] =  ft_strdup(current->data);
			last->args[i + 1] = NULL;
 		}
		current = current->next;
	}
    //print_array(current->args);
}
