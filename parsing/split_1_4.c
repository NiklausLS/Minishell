//header

#include "../includes/minishell.h"

int split_1(t_split_data **split_data, int *i, char *input_line)
{
    if (input_line[*i] == '$')
    {
        if ((*split_data)->temp_last->between_single_quotes != 1)
        {
            if (replace_dollar(*split_data, input_line, i) == 1)
                return (1);
        }
        else if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
            return (1);
        return (0);
    }
    //////
    if (input_line[*i] == ';')
    {
        if ((*split_data)->temp_last->between_single_quotes != 1 && (*split_data)->temp_last->between_double_quotes != 1)
        {
            printf("Error, ; is forbidden\n");
            return (3);
        }
        //return (0);
    }
    //////
    return (2);
}

int split_2(t_split_data **split_data, int *i, char *input_line)
{
    if (input_line[*i + 1] == '\0')
    {
        if (((*split_data)->temp_last->between_single_quotes == 1 && input_line[*i] != '\'') || ((*split_data)->temp_last->between_double_quotes == 1 && input_line[*i] != '"'))
        {
            printf("Error 1, quotes not closed before EOF\n");//
            //return (1);
            //printf("ICI_3\n");//
            return (3);
        }
        if ((*split_data)->temp_last->between_double_quotes != 1 && (*split_data)->temp_last->between_single_quotes != 1 
        && (input_line[*i] == '\'' || input_line[*i] == '"'))
        {
            printf("Error 2, quotes not closed before EOF\n");//
            //return (1);
            return (3);
        }
    }
    return (2);
}

int split_3(t_split_data **split_data, int *i, char *input_line)
{
    if (input_line[*i] == ' ' || input_line[*i] == '\n' || input_line[*i] == '\t')
    {
        if ((*split_data)->temp_last->between_double_quotes == 1 || (*split_data)->temp_last->between_single_quotes == 1)
        {
            if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
                return (1);
            return (0);
        }
        if ((*split_data)->temp_last->data != NULL)
            (*split_data)->new_struct = 1;
        return (0);
    }
    return (2);
}

int split_4_1(t_split_data **split_data, int *i, char *input_line)
{
    if ((*split_data)->temp_last->between_double_quotes == 1 || (*split_data)->temp_last->between_single_quotes == 1)
    {
        if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
            return (1);
        return (0);
    }
    if ((*split_data)->temp_last->data != NULL)
        (*split_data)->new_struct = 2;
    if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
        return (1);
    return (2);
}

int split_4(t_split_data **split_data, int *i, char *input_line)
{
    int res;

    if (input_line[*i] == '<' || input_line[*i] == '>' || input_line[*i] == '|')
    {
        res = split_4_1(split_data, i, input_line);
        if (res != 2)
            return (res);
        if (input_line[*i] == '<' && input_line[*i + 1] == '<')
        {
            if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
                return (1);
            (*i)++;
        }
        else if (input_line[*i] == '>' && input_line[*i + 1] == '>')
        {
            if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
                return (1);
            (*i)++;
        }
        (*split_data)->new_struct = 1;
        return (0);
    }
    return (2);
}