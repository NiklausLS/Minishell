//header

#include "../includes/minishell.h"

int malloc_inputdata(t_input_data **input_data)
{
    if (!input_data)
    {
        printf("Error, no input_data to malloc\n");
        return (1);
    }
    *input_data = malloc(sizeof(t_input_data));
    if (!(*input_data))
    {
        printf("Error malloc input_data\n");
        return (1);
    }
    (*input_data)->between_double_quotes = 0;
    (*input_data)->between_single_quotes = 0;
    (*input_data)->next_structure_without_space = 0;
    (*input_data)->data = NULL;
    (*input_data)->next_data_same_command_id = NULL;
    (*input_data)->next_command_id = NULL;
    (*input_data)->next = NULL;
    (*input_data)->args = NULL;
    (*input_data)->path = NULL;

    (*input_data)->input_type = -1;
    (*input_data)->input = NULL;
    (*input_data)->output_type = -1;
    (*input_data)->output = NULL;
    (*input_data)->pipe_type = -1;
    (*input_data)->heredoc_delim = NULL;
    (*input_data)->file_type = -1;
    (*input_data)->cmd_type = -1;
    (*input_data)->exec_fail = -1;
    (*input_data)->error = 0,
    (*input_data)->arg_type = -1;
    return (0);
}

int malloc_inputdata_and_data(t_input_data **input_data)
{
    if (!input_data)
    {
        printf("Error, no input_data to malloc\n");
        return (1);
    }
    *input_data = malloc(sizeof(t_input_data));
    if (!(*input_data))
    {
        printf("Error malloc input_data\n");
        return (1);
    }
    (*input_data)->between_double_quotes = 0;
    (*input_data)->between_single_quotes = 0;
    (*input_data)->next_structure_without_space = 0;
    (*input_data)->next_data_same_command_id = NULL;
    (*input_data)->next_command_id = NULL;
    (*input_data)->data = malloc(sizeof(char));
    if (!(*input_data)->data)
    {
        printf("Error malloc inputdata->data\n");
        free(*input_data);
        return (1);
    }
    (*input_data)->data[0] = '\0';
    return (0);
}

int malloc_splitdata(t_split_data **split_data, t_input_data **structure, char *input_line)
{
    if (!split_data)
    {
        printf("Error, no split data to malloc\n");
        return (1);
    }
    *split_data = malloc(sizeof(t_split_data));
    if(!(*split_data))
    {
        printf("Error malloc split_data\n");
        return (1);
    }
    (*split_data)->i = 0;
    (*split_data)->end_word = 0;
    (*split_data)->new_struct = 0;
    (*split_data)->input_line = input_line;
    (*split_data)->temp_last = (*structure);
    (*split_data)->temp_new_struct = NULL;
    return (0);
}