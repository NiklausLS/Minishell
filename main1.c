//header

#include "../includes/minishell.h"

int global_signal_received = 0;

int init_tests_minishell(int *argc, char *argv[])
{
    char    *path;
    int     i;

    path = getenv("PATH");
    if(path == NULL)
    {
        printf("Error no path\n");
        return (1);
    }
    if (*argc > 1)
    {
        printf("Error, too many arguments\n");
        i = 1;
        while (argv[i])
        {
            printf("Wrong arguments : %s\n", argv[i]);
            i++;
        }
        return (1);
    }
    printf("Welcome in Minishell\n");
    return (0);
}


int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


int main(int argc, char *argv[])
{
    t_input_data    *input_data;

    input_data = NULL;
    if (init_tests_minishell(&argc, argv) == 1)
        return (1);
    // if (init_signals_minishell() == 1)
    //     return (1);
    if (malloc_inputdata(&input_data) == 1)
        return (1);
    if (show_minishell(&input_data) == 1)
    {
        clean_input_data(&input_data);
        return (1);
    }
    if (clean_input_data(&input_data) == 1)//
        return (1);//
    return (0);
}