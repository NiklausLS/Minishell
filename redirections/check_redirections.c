/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:56:31 by nileempo          #+#    #+#             */
/*   Updated: 2024/04/20 11:01:31 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list
//check if operator
//split the cmd (operatior/file)

//check if there is an operator
static int	check_if_operators(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			//printf("An operator have been found.\n");
			return (0);
		}
		i++;
	}
	//printf("0 operators found\n");
	return (1);
}

//split the str so i can get the name of the file
void	split_redirection(char *str)
{
	char **split_array;
	int	i;
	int file_index;
	char *file_name;

	i = 0;
	split_array = ft_split(str, ' ');
	while (split_array[i])
	{
		printf("[%d] = %s\n", i, split_array[i]);
		if (check_if_operators(split_array[i]) == 0)
		{
			printf("An operator have been found at [%d].\n", i);
			file_index = i + 1;
			printf("file index is : %d\n", file_index);
			file_name = ft_strdup(split_array[file_index]);
			printf("file name is : %s\n", file_name);
		}
		i++;
	}
}

// TO DO LIST
// Check les droits d'ouverture en fonction de l'opérateur
