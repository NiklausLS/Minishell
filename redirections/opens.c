#include "../includes/minishell.h"

/*
 * Open if there is an input
 */
int	open_input(t_token *data)
{
	int	fd;
	t_token *current;

	fd = -1;
	current = data;
	printf("--- in open_input\n");
	if (current->type == INPUT && current->next)
	{
		//printf("Calling open_intput for %s\n", current->next->data);
		fd = open(current->next->value, O_RDONLY, 0644);
		printf("- fd = %d\n", fd);
		if (fd == -1)
		{
			//printf("test input\n");
			print_error(0, current->next->value);
			current->exec_fail = 1;
			return (-1);
		}
	}
	/*else if (cmd->input_type == 1)
	{
		make_input_heredoc(cmd->input);
		return (fd);
	}*/
	//printf("end of open_input loop\n");
	return (fd);
}

/*
 * open if there is an output
 */
int	open_output(t_token *data)
{
	int	fd;
	t_token *current;

	fd = -1;
	current = data;
	printf("IN OPEN OUTPUT\n");
	if (current->type == OUTPUT && current->next)
	{
		fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("--- opening %s\n", current->next->value);
		printf("--- op %s\n", current->next->value);
		if (fd == -1)
		{
			print_error(1, current->next->value);
			current->exec_fail = 1;
			current->error = 1;
            return (-1);
		}
		else
			printf("--- File %s is created\n", current->output);
	}
	else if (current->type == APPEND && current->next)
	{
		fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(1, current->next->value);
			current->exec_fail = 1;
			current->error = 1;
            return (-1);
		}
		else
			printf("File %s is created\n", current->value);
	}
	return (fd);
}