//header

#include "../includes/minishell.h"

int	parse_redirection(t_input_data *current)
{
    int redir_type;

    //printf("*** IN_PARSE_redirection\n");
	redir_type = -1;
    if (!current)
    {
        printf("PARSE_REDIRECTION ERROR\n");
        return (-1);
    }
    if (current->quotes == 0)
        redir_type = check_redirection(current->data);//manque
    else
        return (-1);
    //printf("- IN_PARSE_redirection\n");
    //printf("-- redir_type = %d\n", redir_type);
    //if (current->next->file_type != 1)
    //   print_error(1, current->next->cmd);
    if (redir_type == 0 || redir_type == 1)
    {
        current->input_type = redir_type;
        if (current && current->next)
        {
            current->input = ft_strdup(current->next->data);
            //printf("--- current->input = %s\n", current->input);
            current->next->cmd_type = -1;
            current->next->file_type = 1;
            current->next->arg_type = -1;
            if (current && current->next && current->next->next)
                current->next->next->arg_type = 1;
        }
        //printf("--- current->input_type = %d\n", current->input_type);
    }
    else if (redir_type == 2 || redir_type == 3)
    {
        current->output_type = redir_type;
        if (current && current->next)
        {
            current->output = ft_strdup(current->next->data);
            //printf("--- current->output = %s\n", current->output);
            current->next->cmd_type = -1;
            current->next->file_type = 1;
            current->cmd_type = -1;
            current->next->arg_type = -1;
            if (current && current->next && current->next->next)
                current->next->next->arg_type = 1;
        }
        //printf("--- current->output_type = %d\n\n", current->output_type);
    }
	return (0);
}

int	parse_pipe(t_input_data *current)
{ 
    //printf("in parse_pipe\n");
    int res_pipe;

    res_pipe = -1;
    if (!current)
    {
        ft_putstr_fd("ERROR : parse_pipe is empty\n", 2);
        return (-1);
    }
    if (current->quotes == 0)
        res_pipe = check_pipe(current->data); //manque
    //printf("res_pipe = %d\n", res_pipe);
    //printf("in parse_pipe\n");
    //printf("cmd = %s\n", current->args[0]);
    if (res_pipe == 0)
    {
        current->pipe_type = 1;
        current->cmd_type = -1;
        current->arg_type = -1;
        //printf("%s is a pipe\n", current->cmd);
    }
	return (res_pipe);
}