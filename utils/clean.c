//header

#include "../includes/minishell.h"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////    NORMINETTE////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int clean_input_data2(t_input_data **temp_input, t_input_data **temp_next)
{
    while (*temp_input)
    {
        if ((*temp_input)->data)
        {
            free((*temp_input)->data);
        //if ((*temp_input)->data)
            (*temp_input)->data = NULL;
        }
        if ((*temp_input)->next_data_same_command_id)
        {
            *temp_next = (*temp_input)->next_data_same_command_id;
            free(*temp_input);
            *temp_input = *temp_next;
        }
        else if ((*temp_input)->next_command_id)
        {
            *temp_next = (*temp_input)->next_command_id;
            free(*temp_input);
            *temp_input = *temp_next;
        }
        else
        {
            free(*temp_input);
            *temp_input = NULL;
        }
    }
    return (0);
}
//////////////////////////////////////////////////////////////////////////////////
int clean_input_data(t_input_data **input_data)
{
    t_input_data *temp_next;

    temp_next = NULL;
    if (!input_data || !(*input_data))
        return (0);
    if (clean_input_data2(input_data, &temp_next) == 1)
    {
        free(*input_data);
        return (1);
    }
    return (0);
}

int clean_input_data_reallocate(t_input_data **input_data, int malloc_data)
{
    if (malloc_data != 1 && malloc_data != 0)
    {
        printf("Error, wrong malloc_data input number\n");
        return (1);
    }
    if (clean_input_data(input_data) == 1)
        return (1);
    if (malloc_data == 0)
        if (malloc_inputdata(input_data) == 1)
            return (1);
    if (malloc_data == 1)
        if (malloc_inputdata_and_data(input_data) == 1)
            return (1);
    return (0);
}