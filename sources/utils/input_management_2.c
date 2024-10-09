/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_management_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:38:35 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/09 23:12:48 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	treat_dollar(t_input *input, t_exec *ex, char *tk_input, int i)
{
	char	*tmp;
	int		index;
	int		start;

	i++;
	if (input->left[i] == '?')
	{
		tmp = ft_itoa(ex->last_status);
		ft_strlcat(tk_input, tmp, ft_strlen(tk_input) + ft_strlen(tmp) + 1);
		free(tmp);
	}
	else
	{
		start = i;
		while (i < input->i - 1 && !ft_ischarset(input->left[i + 1], "\"'<>| "))
			i++;
		index = find_env_len(input->left + start, ex->env, (i - start) + 1);
		if (index != -1)
			ft_strlcat(tk_input, ex->env[index] + (i - start) + 2,
				ft_strlen(tk_input) + ft_strlen(ex->env[index]));
	}
	return (i);
}

static void	define_input(t_input *input, t_exec *ex, char *tk_input)
{
	int		i;
	int		start;

	i = -1;
	while (++i < input->i)
	{
		start = i;
		while (i < input->i && (input->left[i] != '$' || i == input->i - 1
				|| (input->left[i + 1] && input->left[i + 1] == ' ')))
			i++;
		ft_strlcat(tk_input, input->left + start, ft_strlen(tk_input)
			+ (i - start) + 1);
		if (i < input->i && input->left[i] == '$' && input->left[i + 1] != ' ')
			i = treat_dollar(input, ex, tk_input, i);
	}
}

static void	ft_create_token(t_input *input, t_token_type type, t_exec *ex)
{
	char	tk_input[70000];

	ft_bzero(tk_input, 70000);
	define_input(input, ex, tk_input);
	remove_quotes(tk_input);
	add_token(input, new_token(ft_strdup(tk_input), type));
	if (input->left[input->i] == ' ')
		input->i++;
	input->left += input->i;
	input->i = 0;
}

static void	ft_tokenization(t_input *input, t_exec *ex)
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
		ft_exit(input, ex);
	input->total = ft_strtrim_ws(input->total);
	if (*input->total == '\0')
		return (0);
	if (ft_strcmp(input->total, "") != 0)
		add_history(input->total);
	input->i = 0;
	input->j = 0;
	input->token_nb = 0;
	input->tokens = NULL;
	input->left = input->total;
	ft_tokenization(input, ex);
	return (1);
}
