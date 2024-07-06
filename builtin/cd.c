/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:31:04 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/06 08:55:22 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

//to do list 
//cd with only a relative or absolute path

/*static void	*get_path(char **argv)
{
	char *home;

	home = getenv("HOME");
	if (argv[1] == NULL | ft_strncmp(argv[1], "~", 1) == 0)
	{
		if (home == NULL)
		{
			ft_putstr_fd("Minishell: cd: Home not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	return (argv[1]);
}*/

/*static int	change_dir(char *dir)
{
	if (chdir(dir) != 0)
	{
		print_error_cd(dir);
		return (1);
	}
	return (0);
}*/

int	make_cd(char **argv)
{
	char	*dir;

	if (argv[1] == NULL || ft_strncmp(argv[1], "~", 1) == 0)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			ft_putstr_fd("Minishell: cd: Home not set\n", 2);
			return (1);
		}
	}
	else
		dir = argv[1];
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		perror(dir);
		return (1);
	}
	return (0);
}
