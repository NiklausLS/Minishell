/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:56:31 by nileempo          #+#    #+#             */
/*   Updated: 2024/06/20 03:42:36 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list
//check if operator
//split the cmd (operatior/file)

//check if there is an operator
static int	check_if_operators(char *str)
{
	int	i;

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
	int		i;
	int		file_index;
	char	*file;

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

//check the operator sign
//< redirige l'entrée vers le fichier
//<< va démarer here_doc ? 
/*
 * @param a string
 * @returns 0 if < is found
 * @returns 1 if << is found
 * @returns -1 if none of them is found
*/
int	check_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			printf("input_redirection : < found.\n");
			return (0);
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			printf("input_redirection : << found.\n");
			return (1);
		}
		if (str[i] == '>')
		{
			printf("output_redirection : > found.\n");
			return (2);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			printf("output_redirection : >> found.\n");
			return (3);
		}
		i++;
	}
	printf("no redirection sign found\n");
	return (-1);
}

int	check_before_after(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_redirection(&str[i]) != -1)
		{
			if (data->path != NULL)
				make_redirection(&str[i + 1]);
			return (0);
		}
	}
	return (1);
}
// TO DO LIST
// Check les droits d'ouverture en fonction de l'opérateur
