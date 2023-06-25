/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:59 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/25 02:03:09 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool is_valid_arg(char *string)
{
    int i;

    i = 0;
    while (string[i])
    {
        if (string[i] < '0' || string[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

bool check_args(int argc, char **argv)
{
    long argument;
    int i;

    i = 0;
    while (++i < argc)
    {
        argument = ft_atol(argv[i]);
        if (!is_valid_arg(argv[i]) || argument > INT_MAX)
            return (false);
    }
    return (true);
}

void end_program(t_table *table, char *error)
{
    if (error)
        write(2, error, strlen(error));
    if (table)
    {
/*         destroy_mutexes(table);
        destroy_philosophers(table); */
        //free(table);
    }
}
