//header
//A NE PAS UTILISER


#include "../includes/minishell.h"

void output_line(char **line)
{
    if (line && *line)
    {
        printf("Line: %s\n", *line);
        free(*line);
        *line = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int execution_minishell(t_input_data *input_data)
{
    //tester si Ctrl-D appuyé pendant l'execution
    //mettre à jour les signaux
    //code d'execution de minishell
    //Tester plusieures executions différentes d'affiler
/*
    int ctrl_d;

    ctrl_d = handle_eof();
    ici
    //ctrl_d exit shell even if line being read
    while(global_signal_received != SIGINT && (handle_eof() == 0))
    {
       ctrl_d = handle_eof();
    }
    return (0);
*/
    //printf("Works up to here\n");
    //printf("Global value : %d\n", global_signal_received);

    char            *line;
    t_input_data    *temp;

    /////////////////////////
    int res;
    printf("TEST BUILTINS\n");
    res = structure_builtins_echo(input_data);
    printf("END BUILTINS, RES = %d\n", res);
    /////////////////////////
    line = NULL;
    temp = input_data;
    while (temp)
    {
        if (temp->data && (ft_strcmp(temp->data, "<") == 0 || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, "<<") == 0 || ft_strcmp(temp->data, ">>") == 0 || ft_strcmp(temp->data, "|") == 0))
        {
            if (line)
                output_line(&line);
            if (add_string_to_string(temp->data, &line) == 1)
                return (1);
            output_line(&line);
        }
        else
        {
            if (add_string_to_string(temp->data, &line) == 1)
                return 1;
            if (temp->next_data_same_command_id && !temp->next_structure_without_space)
            {
                line = add_char_to_string(&line, ' ');
                if (!line)
                {
                    printf("Error allocating malloc\n");
                    return (1);
                }
            }
        }
        if (temp->next_command_id)
        {
            output_line(&line);
            temp = temp->next_command_id;
        }
        else
        {
            temp = temp->next_data_same_command_id;
        }
    }
    output_line(&line);
    return (0);
}
//////////////////////////////////////////////////////////////////////////////////