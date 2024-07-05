/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:17 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 17:04:26 by nileempo         ###   ########.fr       */
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
    new_node->env = NULL;
    new_node->input_type = -1;
    new_node->input = NULL;
    new_node->output_type = -1;
    new_node->output = NULL;
    new_node->heredoc_delim = NULL;
    new_node->next = NULL;
    new_node->pipe_type = -1;
    new_node->file_type = -1;
    new_node->cmd_type = -1;
    new_node->exec_type = -1;
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

/*void    init_redirections_lst(t_data *data)
{
    t_commands *current;
    t_redirection *new_redir;
    
    current = data->cmd_lst;
    while (current)
    {
        if (current->input_type != 1)
        {
            new_redir = malloc(sizeof(t_redirection));
            {
                if (new_redir)
                {
                    new_redir->file = ft_strdup(current->input);
                    new_redir->type = current->input_type;
                    new_redir->next = data->redir_lst;
                    data->redir_lst = new_redir;
                }
            }
        if (current->output_type != 1)
        {
            new_redir = malloc(sizeof(t_redirection));
            {
                if (new_redir)
                {
                    new_redir->file = ft_strdup(current->output);
                    new_redir->type = current->output_type;
                    new_redir->next = data->redir_lst;
                    data->redir_lst = new_redir;
                }
            }
        }
        current = current->next;
    }
}*/

/*
void    add_redirection_node(t_commands *cmd, char *file, int type)
{
    t_redirection *new;
    t_redirection  *add;

    new = (t_commands *)malloc(sizeof(t_redirection));
    new->file = ft_strdup(file);
    new->type = type;
    new->next = NULL;
    if (cmd->redirections == NULL)
        cmd->redirections = new;
    else
    {
        add = cmd->redirections;
        while (add->next)
            add = add->next;
        add->next = new;
    }
}*/

/*
t_commands *make_node()
{
    t_commands *cmd;

    cmd = (t_commands *)malloc(sizeof(t_commands));
    if (!cmd)
        return (NULL);
    ft_memset(cmd, 0, sizeof(t_commands));
    cmd->args = (t_commands *)malloc(sizeof(t_commands));
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    return (cmd);
}

t_commands *parse_node(char *str)
{
    t_commands *head;
    t_commands *current;

    heal = NULL;
    current = NULL;


}*/