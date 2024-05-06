/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:20:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/04/20 08:52:44 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec_redirect.h"

int main(int argc, char **argv)
{
    //char test[] = "BLABLA TEST < file PIAPIA";
    if (argc > 1)
    {
        //check_if_operators(test);
        manage_redirection(argv[1]);
    }
    return (0);
}