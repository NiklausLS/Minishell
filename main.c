/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:52:21 by chuchard          #+#    #+#             */
/*   Updated: 2024/09/24 18:35:21 by nileempo         ###   ########.fr       */
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

char	*ft_strtrim_ws(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && ft_ischarset(s[i], WHITESPACES))
		i++;
	while (s[i])
	{
		if (ft_ischarset(s[i], WHITESPACES))
		{
			while (s[i] && ft_ischarset(s[i], WHITESPACES))
				i++;
			if (s[i])
				s[j++] = ' ';
			else
				break ;
		}
		s[j++] = s[i++];
	}
	s[j] = 0;
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
    new->exec_fail = -1;
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

char	*remove_char(char *str, char *to_remove)
{
	char	*result;
	char	*dst;

	result = (char *)malloc(ft_strlen(str) + 1);
	if (result == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	dst = result;
	while (*str != '\0')
	{
		if (!ft_ischarset(*str, to_remove))
		{
			*dst = *str;
			dst++;
		}
		str++;
	}
	*dst = '\0';
	return (result);
}

void	ft_free_input_data(t_input *input)
{
	free_tokens(input->tokens);
	if (input->total)
		free(input->total);
	input->tokens = NULL;
}

bool	ft_handle_quotes(t_input *input, char type)
{
	printf("' detected\n");
	input->i++;
	while (input->left[input->i] && input->left[input->i] != type)
		input->i++;
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

void	ft_create_token(t_input *input, t_token_type type)
{
	char *token_input;

	token_input = ft_strndup(input->left, 0, input->i);
	add_token(input, new_token(remove_char(token_input, "\'\""), type));
	if (input->left[input->i] == ' ')
		input->i++;
	input->left += input->i;
	input->i = 0;
}

void ft_tokenization(t_input *input)
{
    t_token_type type;

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
                return;
            else if (ft_ischarset(input->left[input->i], OPERATORS))
            {
                if (ft_handle_operators(input, &type))
                    return;
                break;
            }
            else
                input->i++;
        }
        ft_create_token(input, type);
        //printf("Created token: value='%s', type=%d\n", input->tokens->value, input->tokens->type);
        //print_info(input);
    }
}

int	ft_treat_input(t_input *input)
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
	ft_tokenization(input);
	//printf("Commande exécutée : %s\n", input->total);
	return (1);
}

/*int main(int argc, char **argv, char **envp)
{
    t_minishell ms;
    t_exec ex;

    if (argc == 0)
    {
        printf("argc = %d\n", argc);
        printf("argv[0] = %s\n", argv[0]);
    }
    if (init_exec_structure(&ex, envp) != 0)
    {
        fprintf(stderr, "Failed to initialize exec structure\n");
        return (1);
    }

    ft_bzero(&ms, sizeof(t_minishell));
    signal(SIGINT, handle_sig);
    signal(SIGQUIT, handle_sig);
    while (1)
    {
        if (!ft_treat_input(&ms.input))
            break;
        check_lst(ms.input.tokens);
        exec_all(ms.input.tokens, &ex);
        ft_free_input_data(&ms.input);
    }
	while (1)
{
    if (!ft_treat_input(&ms.input))
        break;
    check_lst(ms.input.tokens);
    exec_all(ms.input.tokens, &ex);
    //ft_free_input_data(&ms.input);
}
    // Print environment after each command
    printf("Current environment:\n");
    for (int i = 0; ex.env[i]; i++)
    {
        printf("%s\n", ex.env[i]);
    }
	}
    //clear_history();
    //free_exec_structure(&ex);
    return (0);
}*/

/*int main(int argc, char **argv, char **envp)
{
    t_minishell ms;
    t_exec ex;

	printf("argv = %s\n", argv[0]);
	printf("argc = %d\n", argc);
    init_exec_structure(&ex, envp);
    while (1)
    {
        if (!ft_treat_input(&ms.input))
            break;
        check_lst(ms.input.tokens);
        exec_all(ms.input.tokens, &ex);
        ft_free_input_data(&ms.input);
        printf("*** ENV NOW\n");
       for (int i = 0; ex.env[i]; i++)
        {
            printf("%s\n", ex.env[i]);
        }
    }
	clear_history();
    free_exec_structure(&ex);
    return 0;
}*/

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
		if (!ft_treat_input(&ms.input))
			break ;
		if (check_lst(ms.input.tokens) != 0)
		{
			ft_putstr_fd("Syntax error\n", 2);
			ft_free_input_data(&ms.input);
			continue ;
		}
		//exec_pipeline(ms.input.tokens, &ex);
		execute_all_commands(ms.input.tokens, &ex);
		//execute_pipeline(ms.input.tokens, &ex);
		ft_free_input_data(&ms.input);
	}
	free_exec_structure(&ex);
	clear_history();
	return (0);
}