/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/08 15:19:23 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//Pour tester en attendant d'avoir le code du mate

t_commands *init_node(char *cmd)
{
    t_commands *new_node;
    
    new_node = (t_commands *)malloc(sizeof(t_commands));
    new_node->cmd = ft_strdup(cmd);
    //printf("init_node = cmd = %s\n", cmd);
    new_node->args = ft_split(cmd, ' ');
    /*int i = 0;
    while (new_node->args[i])
    {
        printf("create node : %s\n", new_node->args[i]);
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
    t_commands *current;
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
