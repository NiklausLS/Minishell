/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/19 18:11:20 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

int main(int argc, char **argv, char **envp)
{
    t_data *data;

    //char *in = "BLABLA TEST < int.txt";
    //char *out = "test out > out.txt";
    data = malloc(sizeof(t_data));
    if (!data)
        ft_errorexit("Memory allocation failed for data structure\n");
    init_struc(data);
    int i = 0;
    if (argc > 1)
    {
        while (i < argc)
        {
            printf("argv[%d] = %s\n", i, argv[i]);
            i++;
        }
        //data->cmd = data->split_args[1];
        //split_path(envp, data);
        data->cmd = argv[1];
        data->path = argv[2];
        get_builtin(argv, data, envp);
        //split_path(envp, data);
        //check_path(data->cmd, data);
        make_path(envp, data, data->cmd);
        //make_env(envp);
        split_redirection(argv[1], data);
        //make_redirection(argv[1]);
        print_array(data->split_args);
    }
    //printf("OUT = ");
    //manage_redirection(out);
    return (0);
}