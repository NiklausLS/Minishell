/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:31:04 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/11 07:55:35 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list 
//cd with only a relative or absolute path

int cd(char **argv)
{
    char    *dir;
    if (argv[1] == NULL || ft_strncmp(argv[1], "~", 1) == 0)
    {
        dir = getenv("HOME");
        if (dir == NULL)
        {
            perror("HOME");
            return (-1);
        }
    }
    if (chdir(dir) == 0)
        printf("chdir OK\n");
    else
        perror("cd");
    return (0);
}