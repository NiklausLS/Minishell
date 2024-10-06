/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:52:21 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/06 18:03:48 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(PROMPT, 1);
	}
	else if (sig == SIGQUIT)
	{
		exit(1);
	}
}

int	skip_quotes(char *s, int i)
{
	char type;
	
	type = s[i];
	i++;
	while (s[i] && s[i] != type)
		i++;
	if (!s[i])
		return (0);
	return (i);
}

char	*ft_strtrim_ws(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_ischarset(s[i], WHITESPACES))
		i++;
	while (s[i])
	{
		if (ft_ischarset(s[i], "\'\""))
			i += skip_quotes(s, i);
		if (ft_ischarset(s[i], WHITESPACES))
		{
			i++;
			while (s[i] && s[i + 1] && ft_ischarset(s[i], WHITESPACES))
				ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - 1);
		}
		else
			i++;
	}
	s[i] = 0;
	return (s);
}

void	print_info(t_input *input)
{
	t_token	*current;

	current = input->tokens;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
	printf("Reste à traiter : %s\n\n", input->left);
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->args = NULL;
    new->path = NULL;
    new->input = NULL;
    new->output = NULL;
    new->heredoc_delim = NULL;
    //new->exec_fail = -1;
	new->error = -1;
	return (new);
}

void	add_token(t_input *input, t_token *new)
{
	t_token	*tmp;

	if (!input->tokens)
		input->tokens = new;
	else
	{
		tmp = input->tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	ft_free_input_data(t_input *input)
{
	free_tokens(input->tokens);
	if (input->total)
		free(input->total);
	input->tokens = NULL;
}

void remove_quotes(char *str)
{
	char type;
	int	i;
    int len = ft_strlen(str);
	
	i = 0;
	while (str[i])
	{
		if (ft_ischarset(str[i], "\'\""))
		{
			type = str[i];
			ft_memmove(&str[i], &str[i + 1], len - i);
			while (str[i] && str[i] != type)
			{
				if (str[i] == 26)
					str[i] = '$';
				i++;
			}
			if (str[i])
				ft_memmove(&str[i], &str[i + 1], len - i);
    		str[len - 2] = '\0';
		}
		else
			i++;
	}
    str[i] = '\0';
}

bool	ft_handle_quotes(t_input *input, char type)
{
	// printf("' detected\n");
	input->i++;
	while (input->left[input->i] && input->left[input->i] != type)
	{
		if(type == '\'' && input->left[input->i] == '$')
			input->left[input->i] = 26;
		input->i++;
	}
	if (!input->left[input->i])
	{
		ft_putendl_fd("Unclosed quotes.", 2);
		return (true);
	}
	return (false);
}

bool	ft_handle_operators(t_input *input, t_token_type *type)
{
	*type = TEXT;
	if (input->left[input->i] == '|')
		*type = PIPE;
	else if (input->left[input->i] == '<')
		*type = INPUT;
	else if (input->left[input->i] == '>')
		*type = OUTPUT;
	if (input->left[input->i + 1]
		&& input->left[input->i] == input->left[input->i + 1])
	{
		(*type)++;
		input->i++;
		if (input->left[input->i] == input->left[input->i + 1])
		{
			ft_putendl_fd("Syntax error", 2);
			return (true);
		}
	}
	input->i++;
	return (false);
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

void	define_input(t_input *input, t_exec *ex, char *token_input)
{
	int		i;
	int		start;
	int		index;

	i = -1;
	while (++i < input->i)
	{
		start = i;
		while (i < input->i && (input->left[i] != '$' || i == input->i - 1
			|| (input->left[i + 1] && input->left[i + 1] == ' ')))
			i++;
		// if (i != start)
		ft_strlcat(token_input, input->left + start, ft_strlen(token_input)
				+ (i - start) + 1);
		if (i < input->i && input->left[i] == '$' && input->left[i + 1] != ' ')
		{
			start = i + 1;
			while (i < input->i - 1 && !ft_ischarset(input->left[i + 1], "\"\'<>| "))
				i++;
			index = find_env_len(input->left + start, ex->env, (i - start) + 1);
			if (index != -1)
				ft_strlcat(token_input, ex->env[index] + (i - start) + 2,
					ft_strlen(token_input) + ft_strlen(ex->env[index]));
		}
	}
}

void	ft_create_token(t_input *input, t_token_type type, t_exec *ex)
{
	char	token_input[70000];

	ft_bzero(token_input, 70000);
	define_input(input, ex, token_input);
	remove_quotes(token_input);
	add_token(input, new_token(ft_strdup(token_input), type));
	if (input->left[input->i] == ' ')
		input->i++;
	input->left += input->i;
	input->i = 0;
	// print_info(input);
}

void	ft_tokenization(t_input *input, t_exec *ex)
{
	t_token_type	type;

	while (input->left[input->i])
	{
		type = TEXT;
		while (input->left[input->i] && (input->i == 0 || (input->i > 0
					&& input->left[input->i - 1] == '\\')
				|| !ft_ischarset(input->left[input->i], OPERATORS))
			&& !ft_ischarset(input->left[input->i], WHITESPACES))
		{
			if ((input->left[input->i] == 39 || input->left[input->i] == 34)
				&& ft_handle_quotes(input, input->left[input->i]))
				return ;
			else if (ft_ischarset(input->left[input->i], OPERATORS))
			{
				if (ft_handle_operators(input, &type))
					return ;
				break ;
			}
			else
				input->i++;
		}
		ft_create_token(input, type, ex);
	}
}

int	ft_treat_input(t_input *input, t_exec *ex)
{
	ft_bzero(input, sizeof(t_input));
	input->total = readline(PROMPT);
	if (input->total == NULL)
		return (0);
	if (ft_strcmp(input->total, "") != 0)
		add_history(input->total);
	ft_strtrim_ws(input->total);
	if (!ft_strcmp(input->total, "exit") || !ft_strcmp(input->total, "quit"))
	{
		free(input->total);
		printf("exit\n");
		exit(0);
	}
	input->i = 0;
	input->j = 0;
	input->token_nb = 0;
	input->tokens = NULL;
	input->left = input->total;
	ft_tokenization(input, ex);
	//printf("Commande exécutée : %s\n", input->total);
	return (1);
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
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (1)
	{
		if (!ft_treat_input(&ms.input, &ex))
			break ;
		if (check_last_node(ms.input.tokens) == 1)
		{
			ft_free_input_data(&ms.input);
			continue ;
		}
		if (check_lst(ms.input.tokens) != 0)
		{
			ft_putstr_fd("Syntax error\n", 2);
			ft_free_input_data(&ms.input);
			continue ;
		}
		//parse_args(ms.input.tokens);
		execute_all_commands(ms.input.tokens, &ex);
		printf("- last_status = %d\n",ex.last_status);
		ft_free_input_data(&ms.input);
	}
	free_exec_structure(&ex);
	//rl_clear_history();
	clear_history();
	return (0);
}
