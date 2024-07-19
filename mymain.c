/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/19 08:08:47 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_token *data;
	t_exec ex;

	data = NULL;
	init_exec_structure(&ex, envp);
	//data.redir_lst = NULL;
	//printf("lanching the program\n");
    if (argc == 0)
	{
        printf("argc = %d\n", argc);
		printf("argv[0 = %s\n]", argv[0]);
	}
	//printf("--- ENV BEFORE ---\n");
	//print_env(&ex);
	add_node(&data, init_node("echo"));
	add_node(&data, init_node("hello"));
	add_node(&data, init_node("f1"));
	add_node(&data, init_node(">"));
	add_node(&data, init_node("f2"));
	add_node(&data, init_node("f3"));

	check_lst(data);
	//init_redirections_lst(&data);
	//print_linked_list(&data);
	exec_all(data, &ex);
	
	//printf("\n--- ENV AFTER ---\n");
	//print_env(&ex);

	free_exec_structure(&ex);
	//mfree_input_data(&data);
    return (0);
}




