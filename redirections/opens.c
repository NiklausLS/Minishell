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
	if (current->type == INPUT)
	{
		//printf("Calling open_intput for %s\n", current->next->data);
		fd = open(current->input, O_RDONLY, 0644);
		printf("- fd = %d\n", fd);
		if (fd == -1)
		{
			//printf("test input\n");
			print_error(0, current->input);
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
	if (current->type == OUTPUT)
	{
		fd = open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("--- opening %s\n", current->output);
		printf("--- op %s\n", current->value);
		if (fd == -1)
		{
			print_error(1, current->output);
			current->exec_fail = 1;
			current->error = 1;
            return (-1);
		}
		else
			printf("--- File %s is created\n", current->output);
	}
	else if (current->type == APPEND)
	{
		fd = open(current->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(1, current->output);
			current->exec_fail = 1;
			current->error = 1;
            return (-1);
		}
		else
			printf("File %s is created\n", current->output);
	}
	return (fd);
}