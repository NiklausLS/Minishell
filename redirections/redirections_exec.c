//header

#include "../includes/minishell.h"

int	exec_all(t_input_data *cmd, t_exec *ex)
{
	t_input_data	*start;
	t_input_data	*current;
	t_input_data	*next;

	start = cmd;
	current = cmd;
	//printf("---IN_EXEC_ALL\n");
	while (current)
	{
		next = current->next;//next_command_id
		if (next && next->pipe_type == 1)
        {
			if (protected_pipe(ex->pipefd) == 1)
                return (1);
        }
		else
			ex->pipefd[WRITE_END] = STDOUT_FILENO;
		if (make_child(start, cmd->next, ex) == 1)
            return (1);
		if (ex->prev_pipe != -1)
			close(ex->prev_pipe);//erreur close
		if (next && next->pipe_type == 1)
		{
			close(ex->pipefd[WRITE_END]);//erreur close
			ex->prev_pipe = ex->pipefd[READ_END];
			start = next->next;//next_command_id
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
	//while (wait(NULL) > 0);
	//printf("end of exec_all\n");
    return (0);
}

int	protected_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error : pipe/n", 2);
		exit(EXIT_FAILURE);
	}
    return (0);
}
