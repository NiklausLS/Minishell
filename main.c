/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 18:48:08 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

/*static void	exec_all(t_commands *cmd, char **envp)
{
    int	pipefd[2];
	int	prev_pipe;
	//t_commands *current;
	
	prev_pipe = -1;
	//current = NULL;
	//printf("---IN_EXEC_ALL\n");
	while (cmd)
	{
		if (cmd->pipe_type == -1 && cmd->input_type == -1 && cmd->output_type == -1)
		{
			//current = cmd;
			if (cmd->next && cmd->next->pipe_type == 1)
				protected_pipe(pipefd);
			else
				pipefd[WRITE_END] = STDOUT_FILENO;

			make_child(cmd, prev_pipe, pipefd, envp);

			if (prev_pipe != -1)
					close(prev_pipe);
					
			if (cmd->next && cmd->next->pipe_type == 1)
			{
				close(pipefd[WRITE_END]);
				prev_pipe = pipefd[READ_END];
			}
			else
				prev_pipe = -1;
		}
	cmd = cmd->next;
	//printf("wait for child process\n");
	}
	while (wait(NULL) > 0);
	printf("end of exec_all\n");
}*/

int main(int argc, char **argv)
{
    t_data data;

	data.cmd_lst = NULL;
	//printf("lanching the program\n");
    if (argc == 0)
	{
        printf("argc = %d\n", argc);
		printf("argv[0 = %s\n]", argv[0]);
	}
	
	//add_node(&data.cmd_lst, init_node("piapipa"));
	//add_node(&data.cmd_lst, init_node("|"));
	//add_node(&data.cmd_lst, init_node("wc"));
	//add_node(&data.cmd_lst, init_node(">"));
	//add_node(&data.cmd_lst, init_node("ls"));
	//add_node(&data.cmd_lst, init_node("|"));
	add_node(&data.cmd_lst, init_node("ls"));
	//add_node(&data.cmd_lst, init_node("wc"));
	add_node(&data.cmd_lst, init_node(">"));
	add_node(&data.cmd_lst, init_node("tests/in.txt"));
	//add_node(&data.cmd_lst, create_node("|"));
	//add_node(&data.cmd_lst, create_node("ls"));
	
	check_lst(&data);
	//print_linked_list(&data);
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




