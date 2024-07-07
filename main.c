/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/07 22:28:00 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

//static void	exec_redirect(t_commands *cmd);

static void	exec_all(t_commands *cmd, t_exec *ex)
{
	//t_exec		ex;
	t_commands	*start;


	//ex.prev_pipe = -1;
	//ex.env = ex->env;
	start = cmd;
	//printf("---IN_EXEC_ALL\n");
	while (cmd)
	{
		if (cmd->next == NULL || cmd->next->pipe_type == 1)
		//if (cmd->cmd_type == 1 || cmd->input_type != -1 || cmd->output_type != -1)
		{
			//printf("cmd = %s\n", cmd->args[0]);
			//printf("cmd->next->pipe_type = %d\n", cmd->next->pipe_type);
			if (cmd->next && cmd->next->pipe_type == 1)
				protected_pipe(ex->pipefd);
			else
				ex->pipefd[WRITE_END] = STDOUT_FILENO;
			//make_pipe(cmd, &prev_pipe, pipefd);
			make_child(start, cmd->next, ex);
			//close_pipe(cmd, &prev_pipe, pipefd);
			if (ex->prev_pipe != -1)
					close(ex->prev_pipe);
			if (cmd->next && cmd->next->pipe_type == 1)
			{
				close(ex->pipefd[WRITE_END]);
				ex->prev_pipe = ex->pipefd[READ_END];
			}
			else
				ex->prev_pipe = -1;
			start = cmd->next;
			//printf("***\nIN EXEC_ALL : cmd = %s\n", cmd->cmd);
		}
		cmd = cmd->next;
		//printf("wait for child process\n");
	}
	while (wait(NULL) > 0);
	//printf("end of exec_all\n");
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
	t_exec ex;

	data.cmd_lst = NULL;
	init_exec_structure(&ex, envp);
	//data.redir_lst = NULL;
	//printf("lanching the program\n");
    if (argc == 0)
	{
        printf("argc = %d\n", argc);
		printf("argv[0 = %s\n]", argv[0]);
	}
	
	//add_node(&data.cmd_lst, init_node("export"));
	//add_node(&data.cmd_lst, init_node("NEWVAR=TESTDELAFONCTION"));
	//add_node(&data.cmd_lst, init_node("ls"));
	//add_node(&data.cmd_lst, init_node("f1"));
	//add_node(&data.cmd_lst, init_node(">"));
	//add_node(&data.cmd_lst, init_node("f2"));
	//add_node(&data.cmd_lst, init_node("f3"));
	//add_node(&data.cmd_lst, init_node("head"));
	//add_node(&data.cmd_lst, init_node("5"));
	//add_node(&data.cmd_lst, init_node("|"));
	//add_node(&data.cmd_lst, init_node("hello"));
	//add_node(&data.cmd_lst, init_node(">"));
	//add_node(&data.cmd_lst, init_node("d"));
	//add_node(&data.cmd_lst, init_node(">"));
	//add_node(&data.cmd_lst, init_node("f2.txt"));
	//add_node(&data.cmd_lst, init_node("wc"));
	//add_node(&data.cmd_lst, init_node("<"));
	//add_node(&data.cmd_lst, init_node("f3.txt"));
	//add_node(&data.cmd_lst, init_node("fichier.txt"));
	//add_node(&data.cmd_lst, init_node("|"));
	//add_node(&data.cmd_lst, init_node("wc"));
	
	check_lst(&data);
	//init_redirections_lst(&data);
	//print_linked_list(&data);
	exec_all(data.cmd_lst, &ex);

	t_commands *current = data.cmd_lst;
	while (current)
	{
		t_commands *tmp = current;
		current = current->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->input)
			free(tmp->input);
		if (tmp->output)
			free(tmp->output);
		free(tmp);
	}
	free_exec_structure(&ex);
    return (0);
}




