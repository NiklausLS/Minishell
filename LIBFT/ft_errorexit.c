/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errorexit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:44:56 by nileempo          #+#    #+#             */
/*   Updated: 2024/02/04 22:52:56 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

//print an error msg or stdr and exit
void	ft_errorexit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
