//header

#include "../includes/minishell.h"

int add_char_and_new_struct(t_split_data *split_data, char data, int no)
{
    t_input_data *temp;

    if (split_data->new_struct == 0)
    {
        //if (split_data->temp_last->between_double_quotes != 1 && split_data->temp_last->between_single_quotes != 1 && split_data->input_line[split_data->i] != '"' && split_data->input_line[split_data->i] != '\'')//
        if (no == 0 && add_char_to_data(split_data->temp_last, data) == 1)
            return (1);
    }
    else
    {
        if (malloc_inputdata(&(split_data->temp_new_struct)) == 1)
            return (1);
        if (no == 0 && add_char_to_data(split_data->temp_new_struct, data) == 1)
            return (1);
        temp = split_data->temp_last;
        split_data->temp_last = split_data->temp_new_struct;
        if (split_data->new_struct == 1)
            temp->next_data_same_command_id = split_data->temp_new_struct;
        else if (split_data->new_struct == 2)
            temp->next_command_id = split_data->temp_new_struct;
        split_data->temp_new_struct = NULL;
        split_data->new_struct = 0;
    }
    return (0);
}

int add_char_to_data(t_input_data *structure, char data)
{
    char    *temp;

    if (!structure)
    {
        if (malloc_inputdata(&structure) == 1)
            return (1);
    }
    temp = add_char_to_string(&(structure->data), data);
    if (!temp)
    {
        free(structure);//pas sur
        return (1);
    }
    structure->data = temp;
    return (0);
}

char    *add_char_to_string(char **string, char new_char)
{
    char    *new_malloc;
    int     i;
    int     len;

    if (new_char == '\0')
        return (*string);
    len = ft_len(*string, '\0');
    if (!string || !(*string))
        new_malloc = malloc(sizeof(char) * 2);
    else
        new_malloc = malloc(len + 2);
    if (!new_malloc)
        return (NULL);
    i = 0;
    while (*string && (*string)[i]) 
    {
        new_malloc[i] = (*string)[i];
        i++;
    }
    new_malloc[i] = new_char;
    new_malloc[i + 1] = '\0';
    if (string && *string)
        free(*string);
    return (new_malloc);
}

int add_string_to_string(char *data, char **line)
{
    int     i = 0;
    char    *temp;

    temp = *line;
    while (data && data[i])
    {
        temp = add_char_to_string(&temp, data[i]);
        if (!temp)
        {
            printf("Error allocating malloc\n");
            return (1);
        }
        i++;
    }
    *line = temp;
    return (0);
}

int     ft_len(char *string_input, char end_char)
{
    int len;

    len = 0;
    if (!string_input)
        return (-1);
    while (string_input[len] != end_char && string_input[len] != '\0')
        len++;
    return (len);
}