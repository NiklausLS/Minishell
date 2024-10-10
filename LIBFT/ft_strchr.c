/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:52:49 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:55:32 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	if (c == '\0')
		return (ptr + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (ptr + i);
		i++;
	}
	return (0);
}
