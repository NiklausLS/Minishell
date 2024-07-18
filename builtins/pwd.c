//header

#include "../includes/minishell.h"

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
/*
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

//=====================================================//*/