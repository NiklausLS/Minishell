//header

#include "../includes/minishell.h"

int	pipe_errors(t_input_data *data)
{
	if (!data)
	{
		ft_putstr_fd("Error, no data\n", 2);
		return (1);
	}
	if (!data->next)
	{
		ft_putstr_fd("No data->next\n", 2);
		return (0);
	}
	if (data->pipe_type == 1)
	{
		if (data->next->pipe_type == 1 && data->quotes == 0)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	if ((data->input_type != -1 || data->output_type != -1) && data->quotes == 0)
	{
		if (data->next->pipe_type == 1)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd(" near unexpected token `|'\n", 2);
			exit(EXIT_FAILURE);
		}
	}
    return (0);
}

//inutile
int	redirection_errors(t_input_data *data)
{
	//printf("in redirection_errors\n");
	//print_node(cmd);
	if (data->input_type == 1 || data->output_type)//check quotes == 0 si verifie redirections
	{
		/*if (cmd->next == )
		{
			printf("test\n");
			print_error(2, "");
			exit(EXIT_FAILURE);
		}*/
		//printf("should work\n");
	}
    return (0);
}