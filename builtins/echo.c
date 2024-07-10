//header

#include "../includes/minishell.h"


//envoyer l'adresse de la structure dès le deuxième élement c'est à dire soit -n soit le debut du echo.

int structure_builtins_echo2(t_input_data *structure, t_input_data **temp, int *no_newline)
{
    /*if (temp && temp->data && ft_strcmp(temp->data, "echo") == 0)
        temp = temp->next_data_same_command_id;*/
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
    //if (!structure || structure->data == NULL)
    //{
    //    write(1, "\n", 1);
    //    return (0);
    //}
    //if (temp && temp->data && ft_strcmp(temp->data, "-n") == 0)
    //{
    //    no_newline = 1;
    //    temp = temp->next_data_same_command_id;
    //}
    if (structure_builtins_echo2(structure, &temp, &no_newline) == 2)
        return (0);
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



/*int structure_builtins_echo(t_input_data *structure)
{
    //envoyer l'adresse de la structure dès le deuxième élement c'est à dire soit -n soit le debut du echo.
    t_input_data    *temp;
    char            *temp2;
    int             no_newline;
    int             len;

    if (!structure || structure->data == NULL)
    {
        write(1, "\n", 1);
        return (0);
    }
    temp = structure;
    temp2 = malloc(sizeof(char) * 3);
    if (!temp2)
    {
        printf("Error malloc temp for built_in echo\n");
        return (1);
    }
    temp2[0] = '-';
    temp2[1] = 'n';
    temp2[2] = '\0';
    if (temp->data == temp2)
    {
        no_newline = 1;
        free(temp2);
    }
    else
    {
        no_newline = 0;
        free(temp2);
    }
    while (temp)
    {
        len = ft_len(temp->data, '\0');
        write(1, temp->data, len);
        if (temp->next_data_same_command_id)
            write(1, " ", 1);
        temp = temp->next_data_same_command_id;
    }
    if (no_newline == 0)
        write(1, "\n", 1);
    printf("TEST\n");
    return (0);
}*/