
#include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
typedef struct s_input_data
{
    int                     between_double_quotes;
    int                     between_single_quotes;
    int                     next_structure_without_space;
    char                    *data;
    struct  s_input_data    *next_data_same_command_id;
    struct  s_input_data    *next_command_id;
}   t_input_data;

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

/*int structure_builtins_echo2(t_input_data *structure, t_input_data **temp, int *no_newline)
{
    if (!structure || structure->data == NULL)
    {
        write(1, "\n", 1);
        return (2);
    }
    if (*temp && (*temp)->data && ft_strcmp((*temp)->data, "-n") == 0)
    {
        *no_newline = 1;
        printf("FIRST Nonewline : %d\n", *no_newline);//
        *temp = (*temp)->next_data_same_command_id;
    }
    return (0);
}*/

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//printf le texte jusqu'à la redirection donc doit decider dans la partie execution si lance la commande ou pas, de même que si la première structure est echo alors lance la structure d'après et si la première structure est différente de echo car données après alors doit envoyer la position que est dans la structure en question ??? mais normalement après echo il y a un espace ou redirection. echo>tt2 donne que newline normalement
//echo$HOME
//bash: echo/home/parrot: Aucun fichier ou dossier de ce type
//donc doit verifier si data est dollar alors pas despace c'est interprété comme un chemin vers un dossier ou un fichier
int structure_builtins_echo(t_input_data *structure)
{
    t_input_data    *temp;
    int             len;
    int             no_newline;
    int             first_arg;

    temp = structure;
    no_newline = 0;
    first_arg = 1;
    if (!structure || structure->data == NULL)
    {
        write(1, "\n", 1);
        return (0);
    }
    if (temp && temp->data && ft_strcmp(temp->data, "echo") == 0)
        temp = temp->next_data_same_command_id;
    if (temp && temp->data && ft_strcmp(temp->data, "-n") == 0)
    {
        no_newline = 1;
        temp = temp->next_data_same_command_id;
    }
    //if (structure_builtins_echo2(structure, &temp, &no_newline) == 2)
    //    return (0);
    while (temp)
    {
        if (!first_arg)
            write(1, " ", 1);
        len = ft_len(temp->data, '\0');
        write(1, temp->data, len);
        temp = temp->next_data_same_command_id;
        first_arg = 0;
    }
    //printf("No newline 2 : %d\n", no_newline);//
    if (!no_newline)
        write(1, "\n", 1);
    else//
        printf("NO NEWLINE");//
    return (0);
}

int main(void)
{
    t_input_data *test;
    t_input_data *test2;
    t_input_data *test3;

    test = malloc(sizeof(t_input_data));
    test2 = malloc(sizeof(t_input_data));
    test3 = malloc(sizeof(t_input_data));
    test->data = "echo";
    test->next_data_same_command_id = test2;
    test->next_command_id = NULL;
    test2->data = "-n";
    test2->next_data_same_command_id = test3;
    test2->next_command_id = NULL;
    test3->data = "hello";
    test3->next_data_same_command_id = NULL;
    test3->next_command_id = NULL;
    structure_builtins_echo(test);
    printf("NEWLINE\n");
    return (0);
}