/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:22:18 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/05 12:25:53 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_str_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**malloc_split(char const *s, char c)
{
	int		t;
	char	**tab;

	if (!s)
		return (NULL);
	t = ft_str_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (t + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

static void	fill_split(char const *s, char c, char **tab)
{
	int		i;
	int		j;
	int		count;
	int		t;

	i = 0;
	t = -1;
	count = ft_str_count(s, c);
	while (++t < count)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		tab[t] = ft_substr(s, j, i - j);
	}
	tab[t] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = malloc_split(s, c);
	if (!tab)
		return (NULL);
	fill_split(s, c, tab);
	return (tab);
}
