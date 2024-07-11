//header

#include "../includes/minishell.h"

int    init_exec_structure(t_exec *ex, char **envp)
{
    int env_i;
    int i;

    ex->prev_pipe = -1;
    ex->pipefd[0] = -1;
    ex->pipefd[1] = -1;
    env_i = 0;
    while (envp[env_i])
        env_i++;
    printf("%d\n", env_i);
    ex->env = malloc(sizeof(char *) * (env_i + 1));
    if (ex->env == NULL)
    {
        ft_putstr_fd("Minishell: malloc: allocation memory failed\n", 2);
        exit(EXIT_FAILURE);//return 
    }
    i = 0;
    while (i < env_i)
    {
        ex->env[i]= ft_strdup(envp[i]);
        i++;
    }
    ex->env[env_i] = NULL;
    //print_array(ex->env);
    return (0);
}

int	check_lst(t_input_data *data)
{
	t_input_data	*current;
	t_input_data	*current_errors;
	int				first_cmd;

	current = data;
	current_errors = data;
    first_cmd = 1;
    printf("IN CHECK LST\n");
	while (current_errors)
	{
		if (pipe_errors(current_errors) == 1)
            return (1);
		/*if (redirection_errors(current_errors) == 1)
            return (1);*/
		current_errors = current_errors->next;
	}
    //printf("après current_error\n");
    while (current)
	{
        printf("current = %s\n", current->data);
        if (first_cmd == 1)
        {
            current->cmd_type = 1;
            first_cmd = 0;
        }
        else
        {
		    //print_node(current);
            if (parse_redirection(current) == 1)
                return (1);
		    if (parse_pipe(current) == 1)
                return (1); 
        }
        if (current->file_type == -1 && current->input_type == -1
                && current->output_type == -1 && current->pipe_type == -1
                    && current->cmd_type == -1)
            current->arg_type = 1;
		//print_node(current);

        /*printf("- cmd = %s\n", current->data);
        printf("- input type = %d\n", current->input_type);
        printf("- output type = %d\n", current->output_type);
        printf("- cmd type = %d\n", current->cmd_type);
        printf("- file type = %d\n", current->file_type);
        printf("- arg type = %d\n", current->arg_type);*/
        //if (current->next)
		current = current->next;//next_data_same_command_id
	}
    return (0);
}

int init_input_data(t_input_data *input_data)
{
    t_input_data    *temp;

    temp = input_data;
    while (temp)
    {
        temp->quotes = temp->between_double_quotes + temp->between_single_quotes;
        if (temp->next_command_id)
        {
            temp->next = temp->next_command_id;
            temp = temp->next_command_id;
        }
        else
        {
            temp->next = temp->next_data_same_command_id;
            temp = temp->next_data_same_command_id;
        }
    }
    return (0);
}

int execution_minishell(t_input_data *input_data, t_exec *ex)
{
    //t_exec  *ex;

    //ex = malloc(sizeof(t_exec));
    /*if (init_exec_structure(ex, *(input_data->env)) == 1)
        return (1);*/
    if (init_input_data(input_data) == 1)
        return (1);
    if (check_lst(input_data) == 1)
        return (1);
    if (parse_args(input_data) == 1)
        return (1);
    printf("ex = %s\n", ex->env[0]);
    /*if (exec_all(input_data, ex) == 1)
        return (1);*/
    /*if (free_exec_structure(ex) == 1)
        return (1);*/
    return (0);
}