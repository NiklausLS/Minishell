//header

#include "../includes/minishell.h"

int split_5_1(t_split_data **split_data, int *i, char *input_line)
{
    int no;//

    no = 0;//
    if ((*split_data)->temp_last->between_double_quotes != 1 && 
        (*split_data)->temp_last->between_single_quotes != 1)
    {
        if ((input_line[*i] == '"' && input_line[*i + 1] == '"') || 
        (input_line[*i] == '\'' && input_line[*i + 1] == '\''))
        {
            (*i)++;
            return (0);
        }
        //pour eviter d ajouter les premieres quotes
        if (input_line[*i] == '\'' || input_line[*i] == '"')//
            no = 1;//
        if (add_char_and_new_struct(*split_data, input_line[*i], no) == 1)
            return (1);
        if (input_line[*i] == '"')
            (*split_data)->temp_last->between_double_quotes = 1;
        if (input_line[*i] == '\'')
            (*split_data)->temp_last->between_single_quotes = 1;
        return (0);
    }
    return (2);
}

int split_5_2(t_split_data **split_data, int *i, char *input_line)
{
    if ((*split_data)->temp_last->between_double_quotes == 1 && (*split_data)->temp_last->between_single_quotes == 0)
    {
        //Pour eviter d ajouter les quotes fermantes
        if (input_line[*i] != '"')//
            if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
                return (1);
        if (input_line[*i] == '"')
        {
            (*split_data)->temp_last->between_double_quotes = 2;
            (*split_data)->new_struct = 1;
            if (input_line[*i + 1] != ' ' && input_line[*i + 1] != '\n' && 
            input_line[*i + 1] != '\t' && input_line[*i + 1] != '\0' && 
            input_line[*i + 1] != '<' && input_line[*i + 1] != '>' && 
            input_line[*i + 1] != '|')
                (*split_data)->temp_last->next_structure_without_space = 1;
            return (0);
        }
        return (0);
    }
    return (2);
}

int split_5_3(t_split_data **split_data, int *i, char *input_line)
{
    if ((*split_data)->temp_last->between_double_quotes == 0 && (*split_data)->temp_last->between_single_quotes == 1)
    {
        //Pour eviter d ajouter les quotes fermantes
        if (input_line[*i] != '\'')//
            if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
                return (1);
        if (input_line[*i] == '\'')
        {
            (*split_data)->temp_last->between_single_quotes = 2;
            (*split_data)->new_struct = 1;
            if (input_line[*i + 1] != ' ' && input_line[*i + 1] != '\n' && 
            input_line[*i + 1] != '\t' && input_line[*i + 1] != '\0' && 
            input_line[*i + 1] != '<' && input_line[*i + 1] != '>' && 
            input_line[*i + 1] != '|')
                (*split_data)->temp_last->next_structure_without_space = 1;
            return (0);
        }
        return (0);
    }
    return (2);
}

int split_5(t_split_data **split_data, int *i, char *input_line)
{
    int res;

    if (input_line[*i] == '\'' || input_line[*i] == '"')
    {
        res = split_5_1(split_data, i, input_line);
        if (res != 2)
            return (res);
        res = split_5_2(split_data, i, input_line);
        if (res != 2)
            return (res);
        res = split_5_3(split_data, i, input_line);
        if (res != 2)
            return (res);
        return (0);
    }
    return (2);
}

int split_6(t_split_data **split_data, int *i, char *input_line)
{
    if (add_char_and_new_struct(*split_data, input_line[*i], 0) == 1)
        return (1);
    if ((*split_data)->temp_last->between_double_quotes != 1 && (*split_data)->temp_last->between_single_quotes != 1 && (input_line[*i + 1] == '\'' || input_line[*i + 1] == '"' || input_line[*i + 1] == '$'))
    {
        (*split_data)->new_struct = 1;
        (*split_data)->temp_last->next_structure_without_space = 1;
    }
    return (2);
}