//header

#include "../includes/minishell.h"

/*int exec_pipe_commands(t_input_data *start, t_input_data *end, t_exec *ex)
{
    pid_t pid;
    int status;

	printf("executing pipe_commands : start = %s, end = %s\n", start->data, end->data);

    if (pipe(ex->pipefd) == -1)
	{
        perror("pipe");
        return (1);
    }
	printf("Pipe created. Read end = %d, Write end = %d\n", ex->pipefd[READ_END], ex->pipefd[WRITE_END]);
    pid = fork();
    if (pid == -1)
	{
        perror("fork");
        return (1);
	}
	printf("TEST ENTRE PID\n");
	if (pid == 0)
	{
		printf("new child process\n");
        if (dup2(ex->pipefd[WRITE_END], STDOUT_FILENO) == -1)
		{
            perror("dup2");
            return (1);
		}
		printf("ex->pipefd[WRITE_END] = %d\n", ex->pipefd[WRITE_END]);
		printf("ex->pipefd[READ_END] = %d\n", ex->pipefd[READ_END]);
		//close(STDOUT_FILENO);
		dup2(ex->pipefd[WRITE_END], STDOUT_FILENO);
		printf("redirecting stdout to pipe write end = %d\n", ex->pipefd[WRITE_END]);
        //close(ex->pipefd[READ_END]);
        //close(ex->pipefd[WRITE_END]);
        exec_command(start, ex);
		printf("fin du processus child\n");
    }
	else
	{
		printf("parent process created, child pid = %d\n", pid);
        if (dup2(ex->pipefd[READ_END], STDIN_FILENO) == -1)
		{
            perror("dup2");
            return (1);
        }
		printf("redirecting stdin to pipe read end: %d\n", ex->pipefd[READ_END]);
        close(ex->pipefd[READ_END]);
        close(ex->pipefd[WRITE_END]);

        exec_command(end, ex);
		printf("Parent process waiting for child\n");
        waitpid(pid, &status, 0);
		printf("Parent process finished waiting for child\n");

    }
	printf("fin de exec_pipe_command\n");
    return (0);
}*/

int	make_child(t_input_data *cmd, t_exec *ex)
{
	pid_t			pid;
	int				status;

	printf("cmd  = %s\n", cmd->data);
	//printf("-----\n");
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork: creation failed\n", 2);
		return (1);
	}
	if (pid == 0)
	{
		printf("child process created for command: %s\n", cmd->data);
		if (make_all_redirections(cmd, NULL) == 1)
            return (1);
		printf("--- executing cmd : %s\n", cmd->data);
		if (cmd->cmd_type == 1)
			exec_command(cmd, ex);
	}
	else
	{
		printf("in parent process : child pid is %d\n", pid);
		waitpid(pid, &status, 0);
	}
    return (0);
}

/*int	exec_command(t_input_data *data, t_exec *ex)
{
	//printf("***---IN_EXEC_COMMAND\n");
	printf("cmd = %s\n", data->data);
	//printf("ex = %s\n", ex->env[0]);

	printf("Executing command: %s\n", data->data);
	printf("TEST EXEC_COMMAND\n");
	if (data->pipe_type == 1)
	{
		printf("LEAVING pipe_type = %d\n", data->pipe_type);
		return (0);
	}
    //printf("Command arguments:\n");
    for (int i = 0; data->args[i]; i++) {
        printf("  - %s\n", data->args[i]);
    
    printf("Command type: %d\n", data->cmd_type);
    //printf("Exec fail flag: %d\n", data->exec_fail);
	if (data->pipe_type == 1)
	{
		printf("LEAVING pipe_type = %d\n", data->pipe_type);
		return (0);
	}
	//printf("cmd->args= %s\n", data->args[0]);
	if (!data->data || !data->args[0])
	{
		ft_putstr_fd("Minishell: command not found\n", 2);
		exit(127);
	}

	//print_node(data.cmd_lst);
	//if (get_builtin(data.cmd_lst->cmd) == 0)
		
	//printf("cmd = %s\n", data.cmd_lst->cmd);
	//printf("cmd->data_type = %d\n", data.cmd_lst->cmd_type);
	if (data->cmd_type == 1 && data->exec_fail == -1)
	{
		//if (get_builtin(data, ex) == 0)
		//	return (0);
		if (make_path(ex, data) == 1)
            return (1);
		if (data->path == NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(data->data, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		printf("---- before execve : cmd = %s\n", data->data);
		if (execve(data->path, data->args, ex->env) == -1)
		{
        	write (2, "Error : execve\n", 16);
        	exit(127);
    	}
	}
    return (0);
}*/

int get_builtin(t_input_data *data, t_exec *ex)
//int get_builtin(t_data *data, char **argv, t_exec *ex)
{
	/*if (ft_strcmp(data->cmd_lst->cmd, "cd") == 0)
	{
		printf("CD USED\n");
		make_cd(&argv[1]);
	}*/
    if (ft_strcmp(data->data, "env") == 0)
	{
		printf("ENV USED\n");
		if (make_env(ex->env) == 1)
            return (1);
        return (0);
	}
	else if (ft_strcmp(data->data, "exit") == 0)
	{
		printf("--- EXIT USED ---\n");
		if (make_exit() == 1)
            return (1);
        return (2);//return sans erreur mais avec exit donc verifier la valeur de exit avec $?
	}
    /*else if (ft_strcmp(cmd->data, "echo") == 0)
    {
        printf("ECHO USED\n");
    }
    else if (ft_strcmp(data->cmd, "pwd") == 0)
    {
        printf("PWD USED\n");
    }*/
    else if (ft_strcmp(data->data, "export") == 0)
    {
        printf("--- EXPORT USED ---\n");
        if (make_export(data, ex) == 1)
            return (1);
        return (0);
    }
    else if (ft_strcmp(data->data, "unset") == 0)
    {
        printf("UNSET USED\n");
        if (make_unset(data, ex) == 1)
            return (1);
        return (0);
    }
    return (-1);
}

int	make_all_redirections(t_input_data *start, t_input_data *end)
{

	//printf("-- start = %s\n", start->data);
	//printf("-- end = %s\n", end->data);
	//printf("$ in make_all_redirections\n");
	//printf("--- current input = %d\n",  start->input_type);
	//printf("--- current output = %d\n",  start->output_type);
	t_input_data	*current;
	t_input_data	*last_output_cmd;
	//t_input_data	*last_input_cmd;
	int			last_input;
	int			last_output;		
	
	current = start;
	last_input = -1;
	last_output = -1;
	last_output_cmd = NULL;
	//last_input_cmd = NULL;
	//print_node(current);
	while (current && end)
	{
		/*printf("- current command = %s\n", current->data);
		printf("- current input = %d\n",  current->input_type);
		printf("- current output = %d\n",  current->output_type);*/
		if (current->input_type == 0)
		{
			printf("-- unsing make_input in make all redirections\n");
			//printf(" * * cmd->input_type = %d et cmd->input = %s\n", current->input_type, current->input);
			if (last_input != -1)
            {
                if (close(last_input) == -1)
                {
                    perror("open");
                    return (1);
                }
            }
			last_input = open_input(current);
			if (last_input == -1)
				return (1);
			printf("-- last input = %d\n", last_input);
		}
		//printf("--- after input type\n");
		if (current->output_type == 2 || current->output_type == 3)
		{
			//printf("-- unsign make_output in make all redirections\n");
			last_output = open_output(current);
			//printf("-- last output = %d\n", last_output);
			if (last_output != -1)
            {
				//close(last_output);
                if (close(last_output) == -1)
                {
                    ft_putstr_fd("Error: close failed\n", 2);
                    return (1);
                }
            }
			last_output_cmd = current;
			//printf("-- last_output_cmd = %s\n", last_output_cmd->output);
		}
		current = current->next;//next_data_same_command_id
	}

	//printf("--- after output type\n");
	/*if (last_input != -1)//inutile normalement car aurait finis la fct
	{
		//last_input = open_input(last_input_cmd);
		//printf("last input = %d\n", last_input);
        if (dup2(last_input, STDIN_FILENO) == -1)
        {
            perror("dup2");
            //close(fd);
            return (1);
        }
		//dup2(last_input, STDIN_FILENO);
        if (close(last_input) == -1)
        {
            perror("open");
            return (1);
        }
		//close(last_input);
	}
	//if (last_input != -1)
	//	dup2(last_input, STDIN_FILENO);*/
	if (last_output_cmd != NULL)
	{
		//printf("--- last_output_cmd = %s\n", last_output_cmd->data);
		last_output = open_output(last_output_cmd);
		//printf("--- last output = %d\n", last_output);
		if (last_output != -1)
		{
			//printf("--- last output = %d\n", last_output);
            if (dup2(last_output, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                //close(fd);
                return (1);
            }
			//dup2(last_output, STDOUT_FILENO);
            if (close(last_output) == -1)
            {
                perror("open");
                return (1);
            }
			//close(last_output);
			//printf("--- output redirection to %s\n", last_output_cmd->output);
		}
	}
	//printf("end of make_all_redirections\n");
    return (0);
}

int	open_input(t_input_data *data)
{
	int	fd;
	t_input_data *current;

	fd = -1;
	current = data;
	printf("--- in open_input\n");
	//while (current)
	//{
		if (current->input_type == 0)
		{
			fd = open(current->input, O_RDONLY, 0644);
			printf("- fd = %d\n", fd);
			if (fd == -1)
			{
				//printf("test input\n");
				print_error(0, current->input);
				current->exec_fail = 1;
				return (-1);
			}
		}
		/*else if (cmd->input_type == 1)
		{
			make_input_heredoc(cmd->input);
			return (fd);
		}*/
		//current = current->next;
	//}
	//printf("end of open_input loop\n");
	return (fd);
}

int	open_output(t_input_data *data)
{
	int	fd;
	t_input_data *current;

	//printf("********************************\n");
	//printf(" *** IN OPEN OUTPUT\n");
	fd = -1;
	current = data;
	//int i = 1;
	//while (current)
	//{
	
	//printf("current->output_type = %d\n", current->output_type);
	if (current->output_type == 2)
	{
		fd = open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//printf("- fd = %d\n", fd);
		//printf("- output = %s\n", current->output);
		//if (fd != -1)
		//	printf("*** %s have been made\n", current->output);
		if (fd == -1)
		{
			//printf("blabla\n");
			print_error(1, current->output);
			//printf("blabla\n");
			current->arg_type = -1;
			current->exec_fail = 1;
			current->error = 1;
            return (-1);
		}
	}
	else if (current->output_type == 3)
	{
		//printf(" - cmd->output_type = 3\n");
		//printf(" - cmd->output = %s\n", current->output);
		fd = open(current->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("FILE %s have been created\n", current->output);
		if (fd == -1)
		{
			print_error(1, current->output);
			current->exec_fail = 1;
			current->error = 1;
            return (-1);
		}
	}
		//current = current->next;
		//i++;
	//}
	//printf("enf of open_output loop\n");
	//printf("*****************************\n");
	return (0);
	//return (fd);
}