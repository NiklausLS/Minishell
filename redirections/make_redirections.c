
#include "../includes/minishell.h"

/*
 * check if there is a input or an output and open it
 */
static int  redirections(t_input_data *current, int *last_input, int *last_output)
{
    //printf("--- current input_type = %d\n", current->input_type);
    //printf("--- current output_type = %d\n", current->output_type);
    if (current->input_type == 0)
	{
		if (*last_input != -1)
		{
            if (close(*last_input) == -1)
            {
                perror("open");
                return (1);
            }
        }
	    *last_input = open_input(current);
        //printf("----- input = %d\n", *last_input);
		if (*last_input == -1)
			return (1);
	}
	if (current->output_type == 2 || current->output_type == 3)
	{
        //printf("Calling open_output for %s\n", current->next->data);
		if (*last_output != -1)
        {
            if (close(*last_output) == -1)
            {
                ft_putstr_fd("Error: close failed\n", 2);
                return (1);
            }
        }
        //printf("Calling open_output for %s\n", current->next->data);
		*last_output = open_output(current);
        //printf("----- output = %d\n", *last_output);
		if (*last_output == -1)
			return (1);
        
    }
    return (0);
}

/*
 * dup the input and check if it worked
 */
static int  dup_input(int fd)
{
    if (fd != -1)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            ft_putstr_fd("Minishell: dup2 stdin error\n", 2);
            close (fd);
            return (1);
        }
        close (fd);
    }
    return (0);
}

/*
 * dup the output and check if it's ok
 */
static int  dup_output(int fd)
{
    if (fd != -1)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            ft_putstr_fd("Minishell: dup2 stdout error\n", 2);
            close (fd);
            return (1);
        }
        close (fd);
    }
    return (0);
}

/*
 * Check every node and open/close input and output accordingly
 */
int	make_all_redirections(t_input_data *start, t_input_data *end)
{
    t_input_data    *current;
    int             last_input;
    int             last_output;

    current = start;
    last_input = -1;
    last_output = -1;

    //printf("--- end = %s\n", end->data);
    //printf("--- MAKE_ALL_REDIRECTIONS\n");
    while (current && current != end)
    {
        //printf("--- testing %s\n", current->data);
        if (redirections(current, &last_input, &last_output) == 1)
            return (0);
        current = current->next;
    }
    if (dup_input(last_input) == 1)
		return (0);
	if (dup_output(last_output) == 1)
		return (0);
    return (0);
}
