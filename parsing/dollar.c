//header

#include "../includes/minishell.h"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int replace_dollar(t_split_data *split_data, char *input_line, int *i)
{
    char    *env;
    char    *temp;
    int     x;

    env = NULL;
    temp = NULL;
    if (input_line[*i + 1] == '?')
    {
        env = getenv("?");
        if (!env)
            env = "0";
        (*i)++;
    }
    else if (input_line[*i + 1] == '$')/*A FAIRE*/
    {
        env = getenv("$");
        (*i)++;
    }
    else if (input_line[*i + 1] == '-')
    {
        //env = getenv("-");
        env = "himBHs";
        (*i)++;
    }
    else if (input_line[*i + 1] == '0')
    {
        //normalement le nom script shell
        env = "Minishell";
        (*i)++;
    }
    else if (input_line[*i + 1] == '#')
    {
        //env = getenv("#");
        env = "0";
        (*i)++;
    }
    else if (input_line[*i + 1] == '*')
    {
        env = getenv("*");
        (*i)++;
    }
    else if (input_line[*i + 1] == '@')
    {
        env = getenv("@");
        (*i)++;
    }
    else if (input_line[*i + 1] == '!')
    {
        env = getenv("!");
        (*i)++;
    }
    else if (input_line[*i + 1] >= '1' && input_line[*i + 1] <= '9')
    {
        env = NULL;
        (*i)++;
    }
    else if ((input_line[*i + 1] >= 'A' && input_line[*i + 1] <= 'Z') ||
            (input_line[*i + 1] >= 'a' && input_line[*i + 1] <= 'z') || 
            input_line[*i + 1] == '_')
    {
        (*i)++;
        while (input_line[*i + 1] && ((input_line[*i + 1] >= 'A' && input_line[*i + 1] <= 'Z') || (input_line[*i + 1] >= 'a' && input_line[*i + 1] <= 'z') ||(input_line[*i + 1] >= '0' && input_line[*i + 1] <= '9') || input_line[*i + 1] == '_'))
        {
            temp = add_char_to_string(&temp, input_line[*i]);
            if (!temp)
            {
                printf("Error allocating malloc\n");
                return (1);
            }
            (*i)++;
        }
        temp = add_char_to_string(&temp, input_line[*i]);
        if (!temp)
        {
            printf("Error allocating malloc\n");
            return (1);
        }
        env = getenv(temp);
    }
    else
    {
        if (add_char_and_new_struct(split_data, input_line[*i], 0) == 1)
            return (1);
    }
    x = 0;
    while (env && env[x])
    {
        if (add_char_and_new_struct(split_data, env[x], 0) == 1)
            return (1);
        x++;
    }
    if (env && input_line[*i + 1] != ' ' && input_line[*i + 1] != '\n' && input_line[*i + 1] != '\t' && input_line[*i + 1] != '\0' && input_line[*i + 1] != '<' && input_line[*i + 1] != '>' && input_line[*i + 1] != '|')
    {
        split_data->temp_last->next_structure_without_space = 1;
    }
    if (env && input_line[*i + 1] != '\0')
    {
        split_data->new_struct = 1;
    }
    if (temp)
        free(temp);
    return (0);
}
////////////////////////////////////////////////////////////