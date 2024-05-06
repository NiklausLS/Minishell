/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:03:10 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:57:21 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_calloc(size_t ecount, size_t esize)
{
	void	*ptr;

	ptr = malloc(ecount * esize);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, ecount * esize);
	return (ptr);
}
