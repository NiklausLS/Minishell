/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/30 07:24:43 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//Pour tester en attendant d'avoir le code du mate


t_commands *create_node(char *cmd)
{
    t_commands *new_node = malloc(sizeof(t_commands));
    new_node->cmd = strdup(cmd);
    new_node->args = ft_split(cmd, ' ');
    new_node->input_fd = -1;
    new_node->output_fd = -1;
    new_node->path = NULL;
    new_node->env = NULL;
    new_node->input_type = 0;
    new_node->input = NULL;
    new_node->output_type = 0;
    new_node->output = NULL;
    new_node->heredoc_delim = NULL;
    new_node->next = NULL;
    return new_node;
}

// Fonction pour ajouter une node à la fin de la liste
void add_node(t_commands **head, t_commands *new_node)
{
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    t_commands *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}
