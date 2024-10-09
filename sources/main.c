/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:52:21 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/09 23:25:13 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		rl_replace_line("", 0);
	}
}

void	ft_free_input_data(t_input *input)
{
	free_tokens(input->tokens);
	if (input->total)
		free(input->total);
	input->tokens = NULL;
}

int	find_env_len(char *to_find, char **env, int len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_exit(t_input *input, t_exec *ex)
{
	ft_free_input_data(input);
	free_exec_structure(ex);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	t_exec		ex;

	(void)argc;
	(void)argv;
	if (init_exec_structure(&ex, envp) != 0)
	{
		ft_putstr_fd("Failed to initialize exec structure\n", 2);
		return (1);
	}
	ft_bzero(&ms, sizeof(t_minishell));
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sig);
		if (ft_treat_input(&ms.input, &ex))
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, handle_sig);
			check_last_node(ms.input.tokens);
			check_lst(ms.input.tokens);
			/*if (check_last_node(ms.input.tokens) == 1)
			{
				ft_free_input_data(&ms.input);
				continue ;
			}
			if (check_lst(ms.input.tokens) != 0)
			{
				ft_putstr_fd("Syntax error\n", 2);
				ft_free_input_data(&ms.input);
				continue ;
			}*/
			execute_all_commands(ms.input.tokens, &ex, &ms);
			ft_free_input_data(&ms.input);
		}
	}
	free_exec_structure(&ex);
	rl_clear_history();
	return (0);
}
