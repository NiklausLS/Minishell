/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:54:04 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:59:25 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	size_little;

	if (little[0] == '\0')
		return ((char *)big);
	if (!little)
		return (NULL);
	if (size == 0)
		return (0);
	size_little = ft_strlen(little);
	while (*big && size_little <= size)
	{
		if (*big == *little && (ft_strncmp(big, little, size_little) == 0))
			return ((char *)big);
		big++;
		size--;
	}
	return (0);
}
