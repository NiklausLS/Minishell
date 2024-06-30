/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/30 22:29:08 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

static void	exec_all(t_commands *cmd, char **envp)
{
    int	pipefd[2];
	int	prev_pipe;
	
	prev_pipe = -1;
	//printf("---IN_EXEC_ALL\n");
	while (cmd)
	{
		if (check_pipe(cmd->cmd) == 0)
		{
			//printf("skip pipe node\n");
			cmd = cmd->next;
			continue;
		}
		//printf("cmd = %s\n", cmd->cmd);
		if (cmd->next && check_pipe(cmd->next->cmd) == 0)
		{
			//printf("making a pipe\n");
			protected_pipe(pipefd);
			//cmd = cmd->next;
			//continue;
		}
		else
			pipefd[WRITE_END] = STDOUT_FILENO;
		//printf("call make_child for %s\n", cmd->cmd);
		make_child(cmd, prev_pipe, pipefd, envp);
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmd->next && check_pipe(cmd->next->cmd) == 0)
		{
			close(pipefd[WRITE_END]);
			prev_pipe = pipefd[READ_END];
			cmd = cmd->next->next;
		}
		else
		{
			prev_pipe = -1;
			cmd = cmd->next;
		}
	}
	//printf("wait for child process\n");
	while (wait(NULL) > 0);
	//printf("end of exec_all\n");
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

	data.cmd_lst = NULL;
	//printf("lanching the program\n");
    if (argc == 0)
	{
        printf("argc = %d\n", argc);
		printf("argv[0 = %s\n]", argv[0]);
	}
	
	add_node(&data.cmd_lst, create_node("piapipa"));
	add_node(&data.cmd_lst, create_node("|"));
	add_node(&data.cmd_lst, create_node("wc"));
	add_node(&data.cmd_lst, create_node("|"));
	add_node(&data.cmd_lst, create_node("ls"));
	//add_node(&data.cmd_lst, create_node(">"));
	//add_node(&data.cmd_lst, create_node("test/in.txt"));
	add_node(&data.cmd_lst, create_node("|"));
	add_node(&data.cmd_lst, create_node("ls"));
	
	check_lst(&data);
	exec_all(data.cmd_lst, envp);

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




