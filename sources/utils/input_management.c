/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:35:45 by chuchard          #+#    #+#             */
/*   Updated: 2024/10/09 20:59:19 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtrim_ws(char *s)
{
	int		i;
	int		j;
	bool	in_quotes;
	bool	in_double_quotes;

	i = 0;
	j = 0;
	in_quotes = false;
	in_double_quotes = false;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double_quotes)
			in_quotes = !in_quotes;
		else if (s[i] == '"' && !in_quotes)
			in_double_quotes = !in_double_quotes;
		if (!ft_ischarset(s[i], WHITESPACES) || in_quotes || in_double_quotes)
			s[j++] = s[i];
		else if (ft_ischarset(s[i], WHITESPACES) && j != 0 && s[j - 1] != ' ')
			s[j++] = ' ';
		i++;
	}
	if (s[j] != ' ')
		i++;
	s[j] = '\0';
	return (s);
}

void	remove_quotes(char *str)
{
	char	type;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
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
	input->i++;
	while (input->left[input->i] && input->left[input->i] != type)
	{
		if (type == '\'' && input->left[input->i] == '$')
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
