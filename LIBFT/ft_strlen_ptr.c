/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:24:08 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/09 19:14:22 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlen_ptr(char *s)
{
	char	*start;

	start = s;
	while (*s)
		s++;
	return ((size_t)(s - start));
}
