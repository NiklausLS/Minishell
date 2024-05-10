/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:27:09 by nileempo          #+#    #+#             */
/*   Updated: 2024/05/10 23:07:38 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_redirect.h"

void    init_struc(t_data *data)
{
    data->split_args = NULL; 
    data->fd = -1;
    data->path = NULL;
    data->cmd = NULL;
}