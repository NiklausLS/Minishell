//header

#include "../includes/minishell.h"

int	make_child(t_input_data *start, t_input_data *end, t_exec *ex)
{
	pid_t			pid;
	t_input_data	*cmd;

	//printf("--- IN MAKE CHILD\n");
	//printf("cmd start = %s\n", start->data);
	//printf("-----\n");
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork: creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	/*if (pid != 0)
		printf("pid different de 0\n");*/
	if (pid == 0)
	{
		//printf("\nin child process\n");
		if (ex->prev_pipe != -1)
		{
            if (dup2(ex->prev_pipe, STDIN_FILENO) == -1)
            {
                perror("dup2");
                //close(fd);
                exit(EXIT_FAILURE);
            }
			//dup2(ex->prev_pipe, STDIN_FILENO);
            if (close(ex->prev_pipe) == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
			//close(ex->prev_pipe);
		}
		if (end && end->pipe_type == 1)
		{
            if (close(ex->pipefd[READ_END]) == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
			//close(ex->pipefd[READ_END]);
            if (dup2(ex->pipefd[WRITE_END], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                //close(fd);
                exit(EXIT_FAILURE);
            }
			//dup2(ex->pipefd[WRITE_END], STDOUT_FILENO);
            if (close(ex->pipefd[WRITE_END]) == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
			//close(ex->pipefd[WRITE_END]);
		}
		//printf("BEFORE MAKE_ALL_REDIRECTION\n");
		make_all_redirections(start, end);
            //return (1);
		//printf("BEFORE EXEC_ALL_COMMAND\n");
		//exec_all_command(start, end, ex);
		//printf("BEFORE EXEC_COMMAND\n");
		cmd = start;
		//printf("--- cmd = %s\n", cmd->data);
		//printf("--- cmd_type is %d\n", cmd->cmd_type);
		while (cmd)
		{
			/*printf("- cmd = %s\n", cmd->data);
			if (cmd->input_type != -1)
        		printf("- input type = %d\n", cmd->input_type);
			if (cmd->output_type != -1)
        	printf("- output type = %d\n", cmd->output_type);
			if (cmd->cmd_type != -1)
        	printf("- cmd type = %d\n", cmd->cmd_type);
			if (cmd->file_type != -1)
        	printf("- file type = %d\n", cmd->file_type);
			if (cmd->arg_type != -1)
        	printf("- arg type = %d\n", cmd->arg_type);
			//printf("--- cmd = %s\n", cmd->data);
			//printf("--- cmd_type is %d\n", cmd->cmd_type);*/
			if (cmd && cmd->cmd_type == 1)
			{
				//printf("executing cmd : %s\n", cmd->data);
				if (exec_command(cmd, ex) != 0)
                    return (1);
				break;
			}
			cmd = cmd->next;//next_data_same_command_id
		}
		//printf("no command found or execution is finished\n");
		return (0);
	}
	/*else
		printf("in parent process : child pid is %d\n", pid);*/
    return (0);
}

int	exec_command(t_input_data *data, t_exec *ex)
{
	//printf("***---IN_EXEC_COMMAND\n");
	//printf("cmd = %s\n", data->data);
	//printf("cmd->args= %s\n", data->args[0]);
	/*if (!data->args || !data->args[0])
	{
		ft_putstr_fd("Minishell: command not found\n", 2);
		exit(127);
	}*/
	//print_node(data.cmd_lst);
	//if (get_builtin(data.cmd_lst->cmd) == 0)
		
	//printf("cmd = %s\n", data.cmd_lst->cmd);
	//printf("cmd->data_type = %d\n", data.cmd_lst->cmd_type);
	if (data->cmd_type == 1 && data->exec_fail == -1)
	//if (data.cmd_lst->input_type != -1 || data.cmd_lst->output_type != -1)
	{
		if (get_builtin(data, ex) == 0)
			exit(EXIT_SUCCESS);
		//get_builtin pas terminée
		//if (make_path(ex, &data) == 1)
		if (make_path(ex, data) == 1)
            return (1);
		if (data->path == NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(data->data, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		//printf("before execve : cmd = %s\n", cmd->data);
		if (execve(data->path, data->args, ex->env) == -1)
		{
        	write (2, "Error : execve\n", 16);
        	exit(127);
    	}
	}
    return (0);
}

int make_path(t_exec *ex, t_input_data *data)
{
    t_input_data *current;
	
	current = data;
    //printf("--- IN_MAKE_PATH\n");
    if (get_path(ex, data) == 1)
        return (1);
    while (current)
    {
        if (current->cmd_type == 1)
        {
            if (check_and_set_path(current) == 1)
                return (1);
        }
        current = current->next;//next_data_same_command_id
    }
    return (0);
}

int check_and_set_path(t_input_data *data)
{
    char **paths;
	int	i;

	if (!data->path)
        return (1);//return 1 car erreur ????
	paths = split_path(data->path);
	i = 0;
    if (paths)
    {
        data->path = find_command(paths, data->args[0]);//check erreur
		while (paths[i])
		{
            free(paths[i]);
			i++;
		}
        free(paths);
    }
    if (!data->path && access(data->args[0], F_OK | X_OK) == 0)
        data->path = ft_strdup(data->args[0]);
    //printf("Command: %s, Path: %s\n", cmd->args[0], cmd->path ? cmd->path : "Not found");
    return (0);
}

char *find_command(char **paths, char *cmd)
{
    int i = 0;
    char *full_path;

    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], cmd);
        if (access(full_path, F_OK | X_OK) == 0)//return erreur access
            return full_path;
        free(full_path);
        i++;
    }
    return (NULL);
}

char **split_path(char *path)
{
    char **paths;
	char *tmp;
    int i;

	paths = ft_split(path, ':');
	tmp = NULL;
	i = 0;
    if (!paths)
        return NULL;
    while (paths[i])
    {
        tmp = paths[i];
        paths[i] = ft_strjoin(tmp, "/");
        free(tmp);
        i++;
    }
    return (paths);
}

int get_path(t_exec *ex, t_input_data *data)
{
    char *path = NULL;
    int i = 0;

    //printf("--- IN GET PATH\n");
    //printf("data->cmd_lst->cmd = %s\n", data->cmd_lst->cmd);
    if (ex->env == NULL || *ex->env == NULL)
        return (1);//1 pour erreur 
    while (ex->env[i])
    {
        if (ft_strncmp(ex->env[i], "PATH=", 5) == 0)
        {
            path = ex->env[i] + 5;
            break;
        }
        i++;
    }
    data->path = path;
    //printf("PATH found: %s\n", path ? path : "Not found");
    return (0);
}

int	make_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

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
	//printf("in make_all_redirections\n");
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
	while (current && current != end)
	{
		//printf("--- current loop\n");
		if (current->input_type != -1)
		{
			//printf(" * unsing make_input in make all redirections\n");
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
		}
		//printf("--- after input type\n");
		if (current->output_type != -1)
		{
			//printf(" * unsign make_output in make all redirections\n");
			//printf(" * * cmd->output_type = %d et cmd->output = %s\n", current->output_type, current->output);
			//if (last_output != -1)
			//	close(last_output);
			last_output = open_output(current);
			if (last_output != -1)
            {
				//close(last_output);
                if (close(last_output) == -1)
                {
                    perror("open");
                    return (1);
                }
            }
            /*else
                exit(EXIT_FAILURE);*/
			last_output_cmd = current;
		}
		current = current->next;//next_data_same_command_id
	}

	//printf("--- after output type\n");
	if (last_input != -1)//inutile normalement car aurait finis la fct
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
	//	dup2(last_input, STDIN_FILENO);
	if (last_output_cmd != NULL)
	{
		last_output = open_output(last_output_cmd);
		if (last_output != -1)
		{
			//printf("last output = %d\n", last_output);
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
		return (0);
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
	//printf("--- in open_input\n");
	//while (current)
	//{
		if (current->input_type == 0)
		{
			//printf("-- before open fd = %d\n", fd);
			fd = open(current->input, O_RDONLY, 0644);
			//printf("- fd = %d\n", fd);
			if (fd == -1)
			{
				//printf("test input\n");
				print_error(0, current->input);
				current->exec_fail = 1;
				exit(EXIT_FAILURE);
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

	//printf("---IN MAKE OUTPUT\n");
	fd = -1;
	current = data;
	//int i = 1;
	//while (current)
	//{
		//printf("open_output nbr %d\n", i);
		if (current->output_type == 2)
		{
			fd = open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			//printf("- fd = %d\n", fd);
			//printf("- output = %s\n", current->output);
			if (fd == -1)
			{
				//printf("blabla\n");
				print_error(1, current->output);
				//printf("blabla\n");
				current->exec_fail = 1;
				current->error = 1;
                return (-1);
			}
		}
		else if (current->output_type == 3)
		{
			//printf(" - cmd->output_type = 3\n");
			//printf(" - cmd->output = %s\n", cmd->output);
			fd = open(current->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	return (fd);
}