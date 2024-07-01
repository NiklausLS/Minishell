/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:56:31 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/01 19:11:39 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list
//check if operator
//split the cmd (operatior/file)

//split the str so i can get the name of the file
/*void	split_redirection(char *str, t_data *data)
{
	int		i;
	int		file_index;
	char	*file;

	i = 0;
	file_index = 0;
	data->cmd_lst->args = ft_split(str, ' ');
	while (data->cmd_lst->args[i])
	{
		printf("[%d] = %s\n", i, data->cmd_lst->args[i]);
		if (check_if_operators(data->cmd_lst->args[i]) == 0)
		{
			printf("An operator have been found at [%d].\n", i);
			file_index = i + 1;
			printf("file index is : %d\n", file_index);
			file = ft_strdup(data->cmd_lst->args[file_index]);
			printf("file name is : %s\n", file);
		}
		i++;
	}
}*/

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
	//printf("---IN_CHECK_REDIRECTION\n");
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i] == '<' && str[i + 1] == '<')
			{
				//printf("input_redirection : << found.\n");
				return (1);
			}
			else
			{
				//printf("input_redirection : < found.\n");
				return (0);
			}
		}
		else if (str[i] == '>')
		{
			if (str[i] == '>' && str[i + 1] == '>')
			{
				//printf("output_redirection : >> found.\n");
				return (3);
			}
			else
				//printf("output_redirection : > found.\n");
				return (2);
		}
		i++;
	}
	printf("no redirections found\n");
	printf("	- - - -\n");
	return (-1);
}

int		check_pipe(char *str)
{
	//printf("---IN_CHECK_PIPE\n");
	if (str == NULL)
		return (-1);
	if (ft_strchr(str, '|' ) != 0)
	{
		//printf("a pipe have been found\n");
		return (0);
	}
	return (-1);
}
