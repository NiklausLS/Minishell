//header

#include "../includes/minishell.h"

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