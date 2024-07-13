//header

#include "../includes/minishell.h"

/*static void wait_for_child(pid_t pid)
{
    int status;

    printf("Parent process waiting for child PID: %d\n", pid);
    waitpid(pid, &status, 0);
    printf("Child process (PID: %d) finished with status: %d\n", 
           pid, WEXITSTATUS(status));
}*/

//DEBUG
void wait_for_children(void)
{
    int status;
    pid_t pid;
    
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("Child process %d exited with status %d\n", 
                   pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status))
        {
            printf("Child process %d killed by signal %d\n", 
                   pid, WTERMSIG(status));
        }
    }
}

static t_input_data	*find_command(t_input_data *start, t_input_data *end)
{
    t_input_data *cmd;
    
    cmd = start;
    while (cmd != end && cmd->cmd_type != 1)
        cmd = cmd->next;
    return (cmd);
}

static	t_input_data *find_command_end(t_input_data *start)
{
	t_input_data	*cmd;

	cmd = start;
	while (cmd && cmd->next)
	{
		if (cmd->next->pipe_type == 1)
			return (cmd);
		if (cmd->next->cmd_type == 1)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

static int	make_child(t_input_data *start, t_input_data *end, t_exec *ex)
{
    pid_t			pid;
    t_input_data	*cmd;

    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("Minishell: fork error\n", 2);
        return (1);
    }
    else if (pid == 0)
    {
		setup_in_and_out(ex);
        if (make_all_redirections(start, end) == 1)
            return (1);
		cmd = find_command(start, end);
        printf("cmd = %s\n", cmd->data);
		//if (cmd == end)
		//	return (0);
        exec_command(cmd, ex);
		return (1);
    }
	return (0);
}

int exec_command(t_input_data *data, t_exec *ex)
{
    //printf("in exec_command\n");
    print_node(data);
    if (data->cmd_type != 1 || data->exec_fail != -1)
        return (0);
    make_path(ex, data);
    //rintf("path =  %s\n", data->path);
	//printf("command = %s\n", data->data);
    if (!data->args)
    {
        data->args = ft_split(data->data, ' ');
        /*int i = 0;
        while (data->args[i])
        {
            printf("data->args[%d] = %s\n", i, data->args[i]);
            i++;
        }*/
    }
    //printf("All arguments:\n");
    /*for (int i = 0; data->args[i] != NULL; i++)
    {
        printf("args[%d] = '%s'\n", i, data->args[i]);
    }*/
    //printf("data->path = %s\n", data->path);
    //printf("before execve\n");
    /*int i = 0;
    while (ex->env[i])
    {
        printf("ex->env[%d] = %s\n", i, ex->env[i]);
        i++;
    }*/
    /*if (fcntl(STDIN_FILENO, F_GETFL) & O_NONBLOCK)
        printf("STDIN is a pipe\n");
    else
        printf("STDIN is not a pipe\n");
    printf("File descriptors:\n");
    printf("STDIN (0): %d\n", fcntl(0, F_GETFD));
    printf("STDOUT (1): %d\n", fcntl(1, F_GETFD));
    printf("STDERR (2): %d\n", fcntl(2, F_GETFD));
    printf("STDOUT (3): %d\n", fcntl(3, F_GETFD));
    printf("STDERR (4): %d\n", fcntl(4, F_GETFD));*/
    //printf("path ok\n");
    /*if (access(data->path, X_OK) == 0)
        printf("path = %s : File is executable\n", data->path);
    else
        perror("access");
    printf("About to execute command\n");
    printf("Process effective UID: %d\n", geteuid());
    printf("Process effective GID: %d\n", getegid());
    write(1, "Test STDOUT\n", 12);
    write(2, "Test STDERR\n", 12);
    fflush(stdout);
    fflush(stderr);*/
    if (execve(data->path, data->args, ex->env) == -1)
    {
        //perror("execve");
        perror("execve failed");
        printf("errno: %d\n", errno);
        exit(127);
    }
    return (0);
}

int exec_all(t_input_data *cmd, t_exec *ex)
{
    //int pipefd[2];
    //int in_fd;
    t_input_data    *current;
    t_input_data    *start;
	t_input_data	*end;
    
    current = cmd;
    start = cmd;
    ex->prev_pipe = STDIN_FILENO;
    while (current != NULL)
    {
		end = find_command_end(current);
        if (current->next && current->next->pipe_type == 1)
        {
            if (setup_pipes(ex) != 0)
                return (1);
		}
        if (make_child(start, end, ex) != 0)
            return (1);
		if (end && end->pipe_type == 1)
        {
			setup_pipe_end(ex);
            current = end->next;
        }
        else
        {
            if (end)
                current = end->next;
            else
                current = NULL;
        }
        start = current;
    }
    wait_for_children();
    return (0);
}