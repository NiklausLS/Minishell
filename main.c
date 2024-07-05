/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/05 15:34:54 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

//static void	exec_redirect(t_commands *cmd);

static void	exec_all(t_commands *cmd, char **envp)
{
    int	pipefd[2];
	int	prev_pipe;
	
	prev_pipe = -1;
	//printf("---IN_EXEC_ALL\n");
	while (cmd)
	{
		if (cmd->args && cmd->args[0] && cmd->cmd_type == 1)
		{
			//exec_redirect(cmd);
			//make_child(cmd, prev_pipe, pipefd, envp);
			//printf("cmd = %s\n", cmd->args[0]);
			//printf("cmd->next->pipe_type = %d\n", cmd->next->pipe_type);
			//if (cmd->next && cmd->next->pipe_type == 1)
			//	protected_pipe(pipefd);
			//else
			//	pipefd[WRITE_END] = STDOUT_FILENO;
			make_child(cmd, prev_pipe, pipefd, envp);

			//if (prev_pipe != -1)
			//		close(prev_pipe);
			//if (cmd->next && cmd->next->pipe_type == 1)
			//{
			//	close(pipefd[WRITE_END]);
			//	prev_pipe = pipefd[READ_END];
			//}
			//else
			//	prev_pipe = -1;
			//printf("***\nIN EXEC_ALL : cmd = %s\n", cmd->cmd);
		}
		cmd = cmd->next;
		//printf("wait for child process\n");
	}
	//while (wait(NULL) > 0);
	printf("end of exec_all\n");
}

/*static void	exec_redirect(t_commands *cmd)
{
	t_commands *current;

	current = cmd;
	while (current->next && current->next->cmd_type == -1)
	{
		if (current->next->input_type != -1 && current->next->output_type != -1)
		{
			if (current->next->input_type != -1)
			{
				cmd->input = current->next->input;
				cmd->input_type = current->next->input_type;
			}
			else if (current->next->output_type != -1)
			{
				cmd->output = current->next->output;
				cmd->output_type = current->next->output_type;
			}
		}
		current = current->next;
	}
}*/

int main(int argc, char **argv, char **envp)
{
    t_data data;

	data.cmd_lst = NULL;
	data.redir_lst = NULL;
	//printf("lanching the program\n");
    if (argc == 0)
	{
        printf("argc = %d\n", argc);
		printf("argv[0 = %s\n]", argv[0]);
	}

	//add_node(&data.cmd_lst, init_node("piapipa"));
	//add_node(&data.cmd_lst, init_node("|"));
	add_node(&data.cmd_lst, init_node("ls"));
	add_node(&data.cmd_lst, init_node(">"));
	//add_node(&data.cmd_lst, init_node("cat"));
	add_node(&data.cmd_lst, init_node("fichier.txt"));
	//add_node(&data.cmd_lst, init_node("|"));
	//add_node(&data.cmd_lst, init_node("ls"));
	//add_node(&data.cmd_lst, init_node("wc"));
	add_node(&data.cmd_lst, init_node("<"));
	//add_node(&data.cmd_lst, init_node("fichier.txt"));
	//add_node(&data.cmd_lst, init_node("|"));
	add_node(&data.cmd_lst, init_node("wc"));
	
	check_lst(&data);

	//init_redirections_lst(&data);
	//print_linked_list(&data);
	exec_all(data.cmd_lst, envp);

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

    return (0);
}




