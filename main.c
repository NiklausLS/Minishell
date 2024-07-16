/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:50:11 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/16 20:50:15 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//static void	exec_redirect(t_input_data *cmd);

void	exec_all(t_input_data *cmd, t_exec *ex)
{
	t_input_data	*start;
	t_input_data	*current;
	t_input_data	*next;

	start = cmd;
	current = cmd;
	//printf("---IN_EXEC_ALL\n");
	while (current)
	{
		next = current->next_command_id;
		if (next || next->pipe_type == 1)
			protected_pipe(ex->pipefd);
		else
			ex->pipefd[WRITE_END] = STDOUT_FILENO;
		make_child(start, cmd->next, ex);
		if (ex->prev_pipe != -1)
			close(ex->prev_pipe);
		if (next && next->pipe_type == 1)
		{
			close(ex->pipefd[WRITE_END]);
			ex->prev_pipe = ex->pipefd[READ_END];
			start = next->next_command_id;
		}
		else
		{
			ex->prev_pipe = -1;
			start = next;
			//printf("***\nIN EXEC_ALL : cmd = %s\n", cmd->data);
		}
		current = start;
		//printf("wait for child process\n");
	}
	while (wait(NULL) > 0);
	//printf("end of exec_all\n");
}

int execution_minishell(t_input_data *input_data)
{
	return (0);
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
	
	//printf("--- ENV BEFORE ---\n");
	//print_env(&ex);
	add_node(&data.cmd_lst, init_node("echo"));
	add_node(&data.cmd_lst, init_node("hello"));
	add_node(&data.cmd_lst, init_node("f1"));
	add_node(&data.cmd_lst, init_node(">"));
	add_node(&data.cmd_lst, init_node("f2"));
	//add_node(&data.cmd_lst, init_node("cat"));
	//add_node(&data.cmd_lst, init_node(">"));
	add_node(&data.cmd_lst, init_node("f3"));
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
	
	//printf("\n--- ENV AFTER ---\n");
	//print_env(&ex);
	/*t_input_data *current = data.cmd_lst;
	while (current)
	{
		t_input_data *tmp = current;
		current = current->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->input)
			free(tmp->input);
		if (tmp->output)
			free(tmp->output);
		free(tmp);
	}*/
	free_exec_structure(&ex);
    return (0);
}




