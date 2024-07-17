/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:05:19 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/17 22:51:16 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Free a simple array
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
 * Free the environement
 */
int    free_exec_structure(t_exec *ex)
{
    int i;

    i = 0;
	//printf("ex->env[i] = %s\n", ex->env[i]);
    if (ex->env != NULL)
    {
        while (ex->env[i])
        {
            free(ex->env[i]);
            i++;
        }
        free(ex->env);
    }
    return (0);
}

/*
 * Free what is on the nodes if there is something
 */
int		free_input_data(t_input_data **input_data)
{
    t_input_data	*current;
	
	current = *input_data;
	if (!input_data || !(*input_data))
		return (1);
	while (current)
	{
		if (current->data)
			free(current->data);
		if (current->input)
			free(current->input);
		if (current->output)
			free(current->output);
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		if (current->args)
			free_array(current->args);
		if (current->next)
			current = current->next;
		//free(current);
	}
	//free(current);
	*input_data = NULL;
	return (0);
}
