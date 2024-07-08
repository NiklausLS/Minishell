//header de 42
#include "Header/minishell.h"
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
//**string != NULL
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






//printf("Empty input, please enter a command.\n");






//write heredoc> au debut
//changer la gestion des signaux lorsque entre dans heredoc et rechanger lorsque ressort.
/*int    heredoc(char **heredoc_char, char *delim)
{
    char    *line;

    if (!heredoc_char || !delim)
    {
        printf("No input char or delim for heredoc\n");
        return (1);
    }
    *heredoc_char = malloc(sizeof(char) * 1);
    if (!heredoc_char)
        return (1);
    (*heredoc_char)[0] = '\0';
    line = NULL;
    //boucle while soit avant soit apres + free \ remettre line a 0\ malloc
    while (42)
    {
        line = readline("Heredoc> ");
        //write(1, "\n", 1);
        //rl_on_new_line();
        //rl_replace_line("", 0);
        //rl_redisplay();
        if (!line)
        {
            printf("Ctrl-D pressed\n");
            if (heredoc_char && *heredoc_char)
            {
                free(*heredoc_char);
                *heredoc_char = NULL;
            }
            return (0);
        }
        if (*line == '\0')
        {
            if (add_char_to_string(heredoc_char, "\n") == 1)
            {
                if (heredoc_char && *heredoc_char)
                {
                    free(*heredoc_char);
                    *heredoc_char = NULL;
                }
                if (line)
                {
                    free(line);
                    line = NULL;
                }
                return (1);
            }
            if (line)
            {
                free(line);
                line = NULL;
            }
        }
        else if (ft_strcmp(line, delim) == 0)
        {
            printf("Heredoc Delim entered\n");
            //faut il rajouter le delim a la fin du fichier ????
            if (line)
            {
                free(line);
                line = NULL;
            }
            return (0);
        }
        else
        {
            if (add_string_to_string(line, heredoc_char) == 1)
            {
                if (heredoc_char && *heredoc_char)
                {
                    free(*heredoc_char);
                    *heredoc_char = NULL;
                }
                if (line)
                {
                    free(line);
                    line = NULL;
                }
                return (1);
            }
            if (line)
                free(line);
        }
        printf("TOTAL INPUT: '%s'", *heredoc_char);//del
    }//le heredoc_char sera a free lors de la sortie du heredoc, si *heredoc == NULL alors cest que signaux si return == 0 et erreur si return == 1
    return (0);
}*/



int heredoc(char **heredoc_char, char *delim)
{
    char    *line;

    if (!heredoc_char || !delim)
    {
        printf("No input char or delim for heredoc\n");
        return (1);
    }
    *heredoc_char = malloc(sizeof(char) * 1);
    if (!(*heredoc_char))
    {
        printf("Error allocation malloc heredoc\n");
        return (1);
    }
    (*heredoc_char)[0] = '\0';
    line = NULL;
    while (42)
    {
        line = readline("Heredoc> ");
        if (!line)
        {
            printf("Ctrl-D pressed\n");
            free(*heredoc_char);
            *heredoc_char = NULL;
            return (0);
        }
        if (ft_strcmp(line, delim) == 0)
        {
            printf("Heredoc Delim entered\n");
            free(line);
            return (0);
        }
        if (add_string_to_string(line, heredoc_char) == 1 || add_string_to_string("\n", heredoc_char) == 1)
        {
            free(*heredoc_char);
            *heredoc_char = NULL;
            free(line);
            return (1);
        }
        free(line);
    }
    return (0);
}//le heredoc_char sera a free lors de la sortie du heredoc, si *heredoc == NULL alors cest que signaux si return == 0 et erreur si return == 1


int main(int argc, char *argv[]) {
    char *heredoc_content = NULL;

    if (heredoc(&heredoc_content, "EOF") == 0) {
        printf("Heredoc content:\n%s\n", heredoc_content);
    } else {
        printf("Error occurred during heredoc\n");
    }

    if (heredoc_content)
        free(heredoc_content);

    return 0;
}




//





//======================================================
//Reste à faire :

    //*****************************
    //- signaux
    //- cas exceptionnels $
    //- norminette
    //*****************************

//======================================================















//====================================================//
//gerer les "" et les ''
int bultins_echo(t_input_data *structure)
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
    return (0);
}


//gerer les "" et les ''
//envoyer la structure ainsi que la ligne et echo prendra la structure dans laquelle il faut rajouter une variable is_text et si redirection et que variable is_text alors print tel quel. Mais ducoup dans le echo il faut aussi gérer les redirections ???
int bultins_echo2(t_input_data *structure)
{
    t_input_data *temp = structure;
    int no_newline = 0;
    int first_arg = 1;

    if (!structure || structure->data == NULL) {
        write(1, "\n", 1);
        return 0;
    }

    // Check for -n option
    if (temp && temp->data && ft_strcmp(temp->data, "-n") == 0) {
        no_newline = 1;
        temp = temp->next_data_same_command_id;
    }

    // Print the rest of the arguments
    while (temp) {
        if (!first_arg) {
            write(1, " ", 1);
        }
        int len = ft_len(temp->data, '\0');
        write(1, temp->data, len);
        temp = temp->next_data_same_command_id;
        first_arg = 0;
    }

    if (!no_newline) {
        write(1, "\n", 1);
    }

    return 0;
}
//=====================================================//
/*
int builtins_pwd()
{
    char    *result;
    int     len;

    result = malloc(sizeof(char) * 1024);
    if (!result)
    {
        printf("Error malloc pwd\n");
        return (1);
    }
    if (getcwd(result, 1024) != NULL)
    {
        len = ft_len(result, '\0');
        write(1, result, len);
        write(1, "\n", 1);
    }
    else
    {
        printf("Error getcwd\n");
        free(result);
        return (1);
    }
    free(result);
    return (0);
}
*/

#include <limits.h>
int builtins_pwd2()
{
    char    *result;
    int     len;

    result = malloc(4096);//PATH_MAX
    if (!result)
    {
        printf("Error, malloc pwd\n");
        return (1);
    }

    if (getcwd(result, 4096) != NULL)
    {
        len = ft_len(result, '\0');
        write(1, result, len);
        write(1, "\n", 1);
    } 
    else 
    {
        printf("Error getting pwd\n");
        free(result);
        return (1);
    }
    free(result);
    return (0);
}

//cd gerer les "" et les ''

//=====================================================//
int handle_eof()//à utiliser en fork pendant l'execution pour detecter si appuie sur ctrl-d
{
    char    *buffer;
    ssize_t bytes_read;

    buffer = malloc(sizeof(char) * 1);
    if (!buffer)
        printf("Error malloc buffer\n");
    if (!buffer)
        return (2);
    bytes_read = read(STDIN_FILENO, buffer, 1);//0 il me semble write(1, X, Xnb) ici c'est 0 au lieu de 1 et read au lieu de write
    if (bytes_read == 0)
    {
        printf("Exiting because Ctrl-D pressed\n");
        global_signal_received = 1;
        return (1);
    }
    if (bytes_read < 0)
    {
        printf("Error reading STDIN_FILENO\n");
        if (buffer)
            free(buffer);
        return (2);
    }
    if (buffer)
        free(buffer);
    return (0);
}

/*
- Il faut remettre la valeur de la variable globale à 0 une fois qu'elle a permis de sortir de la boucle de parsing / filling
- Il faut eventuellement mettre la variable globale à 0 / variable globale = variable globale donc inchangée pour le signal Ctrl-D
- Il faut parser les lignes et les stocker dans la structure
- Il faut remplacer les $
- Il faut effectuer les tests dans le excel --> avec valgrind
- Il faut faire les builtins
- Il faut le mettre à la norme
- Verifier Ctrl-d pendant l'execution et non pas seulement l'entrée donc peut-être un deuxième fork lisant en boucle l'entrée pour vérifier controle d et si fork détecte alors kill le child qui execute et termine le programme ou affiche une nouvelle ligne si ctrl c 
*/

    //gcc -Wall -Werror -Wextra minishell_29.c -lreadline -o minishell
    //valgrind --leak-check=full ./minishell


//=====================================================//
// "  kl | bn|az  "

//"   qs er 'b''n'         p  "

//"     kl >><bn <<> md "md'md" 'po'"

//"<<bn>>'"

//< dsgfdsg'sfgs'"kjkj" "  sqdf'hg" ""''>  sans les <> et avec ou sans l'espace au debut

/*
┌─[parrot@parrot]─[~]
└──╼ $echo $"PATH"
PATH
┌─[parrot@parrot]─[~]
└──╼ $echo "PATH"
PATH
┌─[parrot@parrot]─[~]
└──╼ $echo $"path"
path
┌─[parrot@parrot]─[~]
└──╼ $echo $path

┌─[parrot@parrot]─[~]
└──╼ $echo $PATH
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/home/parrot/.local/bin
*/







//cd Téléchargements/42/moi_minishell
//gcc -Wall -Werror -Wextra minishell_17.c -lreadline -o minishell
//valgrind --leak-check=full ./minishell


//tester lorsque entre une ligne le Ctrl-D et Ctrl-C




/*
j'ai un soucis. Quand l'utilisateur entre
"   qs er 'b''n'         p  "(sans les "") il devrait m'afficher
==============================  FINAL  ==========================
Structure's DATA :

0x4ad7480
DATA: 'qs' bdq: '0' bsq: '0'
NDSC_id : 0x4b1c6b0
NC_ID : (nil)
   ndsc_id

0x4b1c6b0
DATA: 'er' bdq: '0' bsq: '0'
NDSC_id : 0x4b1c7c0
NC_ID : (nil)
   ndsc_id

0x4b1c7c0
DATA: ''b'' bdq: '0' bsq: '2'
NDSC_id : 0x4b1c970
NC_ID : (nil)
   ndsc_id

0x4b1c970
DATA: ''n'' bdq: '0' bsq: '2'
NDSC_id : (0x4b1c971)
NC_ID : (nil)
   nc_id

0x4b1c971
DATA: 'p' bdq: '0' bsq: '2'
NDSC_id : (nil)
NC_ID : (nil)
   nc_id
END Structure DATA
*/