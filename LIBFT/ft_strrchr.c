/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:25:44 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:59:34 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s);
	ptr = (char *)s;
	if (c == '\0')
		return (ptr + ft_strlen(s));
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (ptr + i);
		i--;
	}
	return (0);
}
