/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:48:04 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:56:21 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	if (s < d)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (n > i)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
