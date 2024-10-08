/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:44:23 by nileempo          #+#    #+#             */
/*   Updated: 2024/10/08 21:34:19 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	nbr_ok(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_error(char *arg, char *print, int exit_code, t_exec *ex)
{
	ft_putstr_fd("Minishell: exit :", 2);
	ft_putstr_fd(print, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ex->last_status = exit_code;
}

void	make_exit(t_token *data, t_exec *ex)
{
	parse_args(data);
	printf("in make_exit\n");
	if (data->args[1] && !nbr_ok(data->args[1]))
	{
		printf("data->args[1] = %s\n", data->args[1]);
		print_exit_error(data->args[1], "exit", 255, ex);
	}
	else if (data->args[1] && data->args[2])
	{
		printf("data->args[1] = %s\n", data->args[1]);
		printf("data->args[2] = %s\n", data->args[1]);
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		ex->last_status = 1;
	}
	else if (data->args[1])
	{
		printf("data->args[1] = %s\n", data->args[1]);
		ex->last_status = ft_atoi(data->args[1]) % 255;
	}
	else
		ex->last_status = 0;
	printf("ex->last_status = %d\n", ex->last_status);
}
