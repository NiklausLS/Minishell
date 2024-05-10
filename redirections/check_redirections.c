/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:56:31 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/10 22:01:38 by nileempo         ###   ########.fr       */
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
			printf("An operator have been found.\n");
			return (0);
		}
		i++;
	}
	printf("0 operators found\n");
	return (1);
}

//split the str so i can get the name of the file
void	split_redirection(char *str, t_data *data)
{
	int	i;
	int file_index;
	char *file;

	i = 0;
	file_index = 0;
	data->split_args = ft_split(str, ' ');
	while (data->split_args[i])
	{
		printf("[%d] = %s\n", i, data->split_args[i]);
		if (check_if_operators(data->split_args[i]) == 0)
		{
			printf("An operator have been found at [%d].\n", i);
			file_index = i + 1;
			printf("file index is : %d\n", file_index);
			file = ft_strdup(data->split_args[file_index]);
			printf("file name is : %s\n", file);
		}
		i++;
	}
}

// TO DO LIST
// Check les droits d'ouverture en fonction de l'opérateur
