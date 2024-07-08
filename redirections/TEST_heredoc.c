//header de 42
#include "Header/minishell.h"
/*
int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
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
*/





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

//char    *heredoc_char;

//heredoc(&heredoc_char)

void    signal_handler_heredoc(int signal)
{
    if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
        write(1, "  \b\b  \b\b", 8);
    }
}

int heredoc(char **heredoc_char, char *delim)
{
    int     i;
    char    *line;

    //signal(SIGINT, signal_handler_heredoc);//
    //signal(SIGQUIT, signal_handler_heredoc);//
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
    i = 0;//
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, signal_handler_heredoc);
    while (42)
    {
        line = readline("Heredoc> ");
        if (!line)
        {
            //printf("Ctrl-D pressed\n");
            printf("warning: here-document at line %d delimited by end-of-file (wanted `%s')\n%s", i, delim, *heredoc_char);
            free(*heredoc_char);
            *heredoc_char = NULL;
            //est ce que je te retourne l erreur en sortie dc le printf ou null ????
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
        i++;
    }
    return (0);
}//le heredoc_char sera a free lors de la sortie du heredoc, si *heredoc == NULL alors cest que signaux si return == 0 et erreur si return == 1


//Il faudra réinitialiser la gestion des signaux pour ton code dans les processus enfants

//void reset_signals_execution() {
//    signal(SIGINT, SIG_DFL);
//    signal(SIGQUIT, SIG_IGN);
//}
/*
Comportement attendu : Lorsque l'utilisateur appuie sur Ctrl-C pendant l'exécution d'une commande ou pendant l'attente d'une nouvelle commande dans le shell interactif, le shell doit afficher un nouveau prompt sur une nouvelle ligne.

Si l'utilisateur appuie sur Ctrl-D à l'invite du shell (sans aucune commande en cours), le shell doit se terminer proprement et revenir au terminal ou à l'environnement parent.

Ctrl-C (SIGINT) pendant l'exécution : Oui, cela doit afficher un nouveau prompt sur une nouvelle ligne dans ton shell.

Ctrl-D (EOF) pendant l'exécution : Cela doit entraîner la fermeture propre du shell. Si l'utilisateur appuie sur Ctrl-D alors qu'une commande est en cours d'exécution, tu pourrais envisager de terminer cette commande si c'est applicable, mais en général, cela signale la fin de l'entrée et le shell devrait quitter.

Ctrl-\ (SIGQUIT) : Effectivement, cela ne doit rien faire. Il ne devrait y avoir aucun effet observable lorsque Ctrl-\ est pressé, quel que soit l'état du shell.

DONC CONTROLE C ET CONTROLE D DOIVENT LIBERER LA MEMOIRE 

Fermeture propre : 

Libération de la mémoire : Cela implique de libérer toute mémoire allouée dynamiquement par le shell avant de quitter. Si ton shell a alloué de la mémoire à l'aide de malloc() ou d'autres fonctions similaires, il est bon de s'assurer que cette mémoire est libérée à l'aide de free() pour éviter les fuites de mémoire.

Fermeture des descripteurs de fichiers : Assure-toi que tous les descripteurs de fichiers ouverts sont correctement fermés avant de quitter. Cela inclut notamment les fichiers ouverts à l'aide de open() et close(), ainsi que d'autres descripteurs de fichiers comme ceux associés aux pipes ou aux redirections.

Retour de code : Ton shell devrait retourner un code de sortie approprié à l'environnement qui l'a lancé (par exemple, le terminal ou un script). Un code de sortie conventionnellement utilisé est EXIT_SUCCESS (0) pour indiquer une sortie normale et EXIT_FAILURE (1) pour indiquer une sortie avec erreur.

Nettoyage général : Il peut également être nécessaire de nettoyer d'autres ressources ou états spécifiques à ton shell, en fonction de sa complexité et des fonctionnalités qu'il supporte.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
SINON SIMPLEMENT FAIRE UNE FONCTION SIGNAL QUI CHANGE LE NUMERO DE LA VARIABLE GLOBALE ET LORSQUE LA VARIABLE GLOBALE NEST PLUS 0 ALORS IL FAUT SUPPRIMER LES DONNEES ET EXIT MANUELLEMENT
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/

























/*int main(int argc, char *argv[]) {
    char *heredoc_content = NULL;

    if (heredoc(&heredoc_content, "EOF") == 0) {
        printf("Heredoc content:\n%s\n", heredoc_content);
    } else {
        printf("Error occurred during heredoc\n");
    }
    printf("%d\n%s\n", argc, argv[0]);

    if (heredoc_content)
        free(heredoc_content);

    return 0;
}*/
/*
    LES SIGNAUX CTRL C ETC A REPRENDRE REGARDER ANCIEN GPT
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

/*
   Fermeture des descripteurs de fichiers : Assure-toi que tous les descripteurs de fichiers ouverts sont correctement fermés avant de quitter. Cela inclut notamment les fichiers ouverts à l'aide de open() et close(), ainsi que d'autres descripteurs de fichiers comme ceux associés aux pipes ou aux redirections.
*/