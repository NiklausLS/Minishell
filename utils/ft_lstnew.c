/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/09 17:42:56 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Pour tester en attendant d'avoir le code du mate

t_commands *init_node(char *cmd)
{
    t_commands *new_node;
    
    new_node = (t_commands *)malloc(sizeof(t_commands));
    new_node->cmd = ft_strdup(cmd);
    //printf("init_node = cmd = %s\n", cmd);
    new_node->args = ft_split(cmd, ' ');
    //printf("--- create node args[0] = %s\n", new_node->args[0]);
    /*int i = 1;
    while (new_node->args[i])
    {
        printf("--- create node args[%d] : %s\n", i, new_node->args[i]);
        i++;
    }*/
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
    return (new_node);
}

// Fonction pour ajouter une node à la fin de la liste
void add_node(t_commands **head, t_commands *new_node)
{
    t_data *data;
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
void	add_arg(t_data *data)
{
	t_commands	*current;
	t_commands	*last;
	int			i;

    printf("-- in add_arg\n");
	/*if (!data || data->cmd_lst)
		return ;*/
	last = NULL;
    current = data->cmd_lst;
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
            printf("-- %s is an arg\n", current->cmd);
			while (last->args[i])
				i++;
			last->args[i] =  ft_strdup(current->cmd);
			last->args[i + 1] = NULL;
 		}
		current = current->next;
	}
    //print_array(current->args);
}
