/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nileempo <nileempo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:30:35 by nileempo          #+#    #+#             */
/*   Updated: 2024/07/09 13:47:53 by nileempo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    add_quotes(char *var)
{
    char    *sign;
    size_t  var_len;
    size_t  len;
    char    *new_var;
    
    sign = ft_strchr(var, '=');
    if (!sign)
    {
        sign = ft_strdup(var);
        return (sign);
    }
    var_len = sign - var;
    len = ft_strlen(var_len + 1);
    new_var = (char *)malloc(sizeof(var_len + len + 4));
    if (new_var)
    {
        ft_memcpy(new_var, var, var_len + 1);
        new_var[var_len + 1] = "";
        
    }
}