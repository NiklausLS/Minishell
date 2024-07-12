//header

#include "../includes/minishell.h"

int	check_redirection(char *str)
{
	int	i;

	i = 0;
	//printf("---IN_CHECK_REDIRECTION\n");
	if (str == NULL)
	{
		//ft_putstr_fd("EMPTY STR IN CHECK REDIRECTION\n", 2);
		return (-1);
	}
	while (str && str[i])
	{
		if (str[i] == '<')
		{
			if (str[i] == '<' && str[i + 1] == '<')
				return (1);
			else
				return (0);
		}
		else if (str[i] == '>')
		{
			if (str[i] == '>' && str[i + 1] == '>')
				return (3);
			else
				return (2);
		}
		i++;
	}
	//printf("no redirections found\n");
	//printf("	- - - -\n");
	return (-1);
}

int	check_pipe(char *str)
{
	//printf("---IN_CHECK_PIPE\n");
	if (str == NULL)
	{
		//ft_putstr_fd("EMPTY STR IN CHECK_PIPE\n", 2);
		return (1);
	}
	if (str && str[0] == '|')
	{
		//printf("str[0] = %c", str[0]);
		return (0);
	}
	return (1);
}