/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:42 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/25 01:55:23 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t strlen(const char *string)
{
    size_t i;

    i = 0;
    while (string[i])
        i++;
    return (i);
}

long ft_atol(const char *string)
{
    long result;
    int sign;

    result = 0;
    sign = 1;
    while (*string == ' ' || (*string >= '\t' && *string <= '\r'))
        string++;
    if (*string == '-' || *string == '+')
    {
        if (*string == '-')
            sign = -1;
        string++;
    }
    while (*string >= '0' && *string <= '9')
    {
        result = result * 10 + (*string - '0');
        string++;
    }
    return (result * sign);
}
