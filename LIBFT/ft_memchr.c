/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:10:52 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:56:45 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	target;

	i = 0;
	str = (unsigned char *) s;
	target = (unsigned char) c;
	while (i < n)
	{
		if (str[i] == target)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
