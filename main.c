/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/30 07:49:46 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

/*static void	exec_all(t_commands *cmd, char **envp)
{
    int	pipefd[2];
	int	prev_pipe;
	
	prev_pipe = -1;
	while (cmd)
	{
		if (check_pipe(cmd->next->cmd) == 0 && cmd->next->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		make_child(cmd, prev_pipe, pipefd, envp);
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmd->next != NULL)
		{
			close(pipefd[WRITE_END]);
			prev_pipe = pipefd[READ_END];
		}
		else
			prev_pipe = -1;
		cmd = cmd->next;
		while (wait(NULL) > 0);
	}
}*/

int main(int argc, char **argv)
{
    t_data data;

	data.cmd_lst = NULL;
	printf("lanching the program\n");
    if (argc == 0)
	{
        printf("argc = %d\n", argc);
		printf("argv[0 = %s\n]", argv[0]);
	}
	
	add_node(&data.cmd_lst, create_node("ls"));
	add_node(&data.cmd_lst, create_node("|"));
	add_node(&data.cmd_lst, create_node("wc"));
	add_node(&data.cmd_lst, create_node(">"));
	//add_node(&data.cmd_lst, create_node("test/in.txt"));
	
	check_lst(&data);
	//exec_all(data.cmd_lst, envp);

	t_commands *current = data.cmd_lst;
	while (current)
	{
		t_commands *tmp = current;
		current = current->next;
		free(tmp->cmd);
		free(tmp);
	}

    return (0);
}




