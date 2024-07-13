//header

#include "../includes/minishell.h"

/*int exec_all(t_input_data *cmd, t_exec *ex) {
    t_input_data *current = cmd;
    t_input_data *next;
    pid_t pid;
    int status;

    while (current != NULL)
    {
        next = current->next;
        if (next && next->pipe_type == 1)
        {
            printf("Executing commands with pipe\n");
            printf("ex->prev_pipe = %d\n", ex->prev_pipe);

            if (pipe(ex->pipefd) == -1)
            {
                perror("pipe");
                return 1;
            }
            printf("Created pipe. Read end: %d, Write end: %d\n", ex->pipefd[READ_END], ex->pipefd[WRITE_END]);
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return 1;
            }
            else if (pid == 0)
            {
                printf("Child process created\n");
                if (ex->prev_pipe != -1) {
                    if (dup2(ex->prev_pipe, STDIN_FILENO) == -1) {
                        perror("dup2");
                        return 1;
                    }
                    printf("Redirected stdin to previous pipe: %d\n", ex->prev_pipe);
                    close(ex->prev_pipe);
                }
                if (dup2(ex->pipefd[WRITE_END], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    return 1;
                }
                printf("Redirected stdout to pipe write end: %d\n", ex->pipefd[WRITE_END]);
                close(ex->pipefd[READ_END]);
                close(ex->pipefd[WRITE_END]);
                exec_command(current, ex);
            }
            else
            {
                printf("Parent process created, child PID: %d\n", pid);
                if (ex->prev_pipe != -1) {
                    close(ex->prev_pipe);
                }
                ex->prev_pipe = ex->pipefd[READ_END];
                printf("Stored pipe read end in ex->prev_pipe: %d\n", ex->prev_pipe);
                close(ex->pipefd[WRITE_END]);
                exec_command(next, ex);
                waitpid(pid, &status, 0);
            }
            current = next->next;
        } 
        else
        {
            printf("-- Executing single command\n");
            //printf("-- cmd = %s", current->data);
            if (make_child(current, ex) == 1)
                return (1);
            current = next;
        }
    }
    while (waitpid(-1, NULL, 0) > 0);
    return 0;
}*/

/*int exec_all(t_input_data *cmd, t_exec *ex)
{
    t_input_data *current = cmd;
    t_input_data *next;

    while (current != NULL)
    {
        next = current->next;
        if (next && next->pipe_type == 1)
        {
            printf("Executing commands with pipe\n");
            printf("ex->prev_pipe = %d\n", ex->prev_pipe);
            if (exec_pipe_commands(current, next, ex) == 1)
                return 1;
            current = next->next;
        }
        else
        {
            if (make_child(current, ex) == 1)
                return 1;
            if (exec_only_command(cmd, ex) == 1)
                return (1);
            current = next;
        }
    }

    while (waitpid(-1, NULL, 0) > 0);

    return 0;
}*/

static int create_pipe(t_exec *ex)
{
    if (pipe(ex->pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }
    printf("Created pipe. Read end: %d, Write end: %d\n", 
           ex->pipefd[READ_END], ex->pipefd[WRITE_END]);
    return (0);
}

static void setup_child_for_pipe(t_exec *ex)
{
    if (ex->prev_pipe != -1)
    {
        if (dup2(ex->prev_pipe, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(ex->prev_pipe);
    }
    
    if (dup2(ex->pipefd[WRITE_END], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(ex->pipefd[READ_END]);
    close(ex->pipefd[WRITE_END]);
}

static void setup_parent_for_pipe(t_exec *ex)
{
    if (ex->prev_pipe != -1)
        close(ex->prev_pipe);
    
    ex->prev_pipe = ex->pipefd[READ_END];
    close(ex->pipefd[WRITE_END]);
    
    printf("Stored pipe read end in ex->prev_pipe: %d\n", ex->prev_pipe);
}

static void wait_for_child(pid_t pid)
{
    int status;

    printf("Parent process waiting for child PID: %d\n", pid);
    waitpid(pid, &status, 0);
    printf("Child process (PID: %d) finished with status: %d\n", 
           pid, WEXITSTATUS(status));
}


//DEBUG
static void wait_for_children()
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

static int handle_piped_commands(t_input_data *current, t_exec *ex)
{
    if (create_pipe(ex) != 0)
        return 1;
    
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        setup_child_for_pipe(ex);
        exec_pipe_commands(current, current->next, ex);
        exit(EXIT_FAILURE);
    }
    else
    {
        setup_parent_for_pipe(ex);
        exec_command(current->next, ex);
        wait_for_child(pid);
    }
    return 0;
}

static int execute_single_command(t_input_data *cmd, t_exec *ex)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        if (make_all_redirections(cmd, NULL) != 0)
            exit(EXIT_FAILURE);
        exec_command(cmd, ex);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait_for_child(pid);
    }
    return 0;
}

int exec_command(t_input_data *data, t_exec *ex)
{
    if (data->cmd_type != 1 || data->exec_fail != -1)
        return 0;
    /*if (is_builtin(data))
        return execute_builtin(data, ex);*/
    
    //if (data->path)
    //    printf("path = %s\n", data->path);
        //free(path);
    make_path(ex, data);
    //printf("IN EXEC COMMAND\n");
    printf("path =  %s\n", data->path);
    //printf("Current PATH: %s\n", getenv("PATH"));
    //path = data->path;
    /*if (data->path == NULL)
    {
        //print_command_not_found(data);
        exit(127);
    }*/
    printf("Command: %s\n", data->path);
    if (!data->args)
    {
        data->args = ft_split(data->data, ' ');
        int i = 0;
        while (data->args[i])
        {
            printf("data->args[%d] = %s\n", i, data->args[i]);
            i++;
        }
    }
    printf("data->path = %s\n", data->path);
    printf("before execve\n");
    /*int i = 0;
    while (ex->env[i])
    {
        printf("ex->env[%d] = %s\n", i, ex->env[i]);
        i++;
    }*/
    printf("File descriptors:\n");
    printf("STDIN (0): %d\n", fcntl(0, F_GETFD));
    printf("STDOUT (1): %d\n", fcntl(1, F_GETFD));
    printf("STDERR (2): %d\n", fcntl(2, F_GETFD));
    printf("path ok\n");
    if (access(data->path, X_OK) == 0)
        printf("File is executable\n");
    else
        perror("access");
    printf("About to execute command\n");
    fflush(stdout);
    if (execve(data->path, data->args, ex->env) == -1)
    {
        //perror("execve");
        exit(127);
    }
    return (0);
}



int exec_pipe_commands(t_input_data *start, t_input_data *end, t_exec *ex)
{
    if (create_pipe(ex) != 0)
        return 1;

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        setup_child_for_pipe(ex);
        exec_command(start, ex);
        exit(EXIT_FAILURE);
    }
    else
    {
        setup_parent_for_pipe(ex);
        exec_command(end, ex);
        wait_for_child(pid);
    }
    return (0);
}

int exec_all(t_input_data *cmd, t_exec *ex)
{
    t_input_data *current = cmd;
    while (current != NULL)
    {
        if (current->next && current->next->pipe_type == 1)
        {
            if (handle_piped_commands(current, ex) != 0)
                return (1);
            current = current->next->next;
        }
        else
        {
            if (execute_single_command(current, ex) != 0)
                return 1;
            current = current->next;
        }
    }
    wait_for_children();
    return 0;
}

int	protected_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error : pipe/n", 2);
		return (1);
	}
    return (0);
}
