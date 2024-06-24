/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/24 12:10:12 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

int main(int argc, char **argv, char **envp)
{
    //t_data *data;
    t_data *head = NULL;
    if (argc == 0)
        printf("argc = %d\n", argc);
    printf("argv[0] = %s\n", argv[0]);
    //char *in = "ls > tests/in.txt";
    char    *cmd1[] = {"ls", NULL};
    char    *cmd2[] = {"blabla", NULL};
    //char    *cmd3[] = {"wc", "-l", NULL};

    ft_addlst(cmd1, &head, envp);
    ft_addlst(cmd2, &head, envp);
    //ft_addlst(cmd3, &head, envp);

    print_linked_list(head);
    exec_command(head);
    
    //data = malloc(sizeof(t_data));
    //if (!data)
    //    ft_errorexit("Memory allocation failed for data structure\n");
    //init_struc(data);
    //int i = 0;

    /*while (1)
    {
        input = readline("> ");
        if (input == NULL)
            break;
        data->args = ft_split(input, ' ');
    }*/

    /*if (argc > 0)
    {
        while (argv[i])
        {
            printf("argv[%d] = %s\n", i, argv[i]);
            i++;
        }
        data->args = ft_split(in, ' ');
        print_array(data->args);
        data->cmd = data->args[0];
        printf("cmd = %s\n", data->cmd);
        
        make_path(envp, data, data->cmd);
        make_redirection(in);
        get_builtin(argv, data, envp);
        exec_command(data, &data->cmd, envp);
        //split_redirection(argv[1], data);
        //make_redirection(argv[1]);
        //print_array(data->split_args);
    }*/
    //printf("OUT = ");
    //manage_redirection(out);*/
    return (0);
}