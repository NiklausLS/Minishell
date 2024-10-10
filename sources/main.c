/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:52:21 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/10 08:27:08 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
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
		return (print_error(6, NULL));
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
			execute_all_commands(ms.input.tokens, &ex);
			ft_free_input_data(&ms.input);
		}
	}
	free_exec_structure(&ex);
	rl_clear_history();
	return (0);
}
