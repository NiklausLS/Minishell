//header

#include "../includes/minishell.h"

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