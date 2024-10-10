/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:50:55 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:59:42 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s || start > ft_strlen(s))
		return (ft_calloc(1, 1));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			str[i] = s[start + i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
