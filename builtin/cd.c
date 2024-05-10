/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:31:04 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/10 23:50:24 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list 
//cd with only a relative or absolute path

void    cd(char *path)
{
    printf("Path before : %s\n", path);
    if (path == NULL)
    {
        path = getenv("HOME");
        if (path == NULL)
        {
            perror("path");
            return ;
        }
    }
    printf("Path after : %s\n", path);
    if (chdir(path) == 0)
        printf("chdir OK\n");
    else
        perror("cd");
}