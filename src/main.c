/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:45 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/25 02:04:23 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_table *table;
    char *status;

    status = NULL;
    if (argc < 5 || argc > 6)
        return (end_program(table, ERR_ARGC), EXIT_FAILURE);
    if (!check_args(argc, argv))
        return (end_program(table, ERR_ARGV), EXIT_FAILURE);
    if (!init_table(table, argc, argv, &status))
        return (end_program(table, status), EXIT_FAILURE);
/*     if (!create_philosophers(table, &status))
        return (end_program(table, status), EXIT_FAILURE);
    if (!join_philosophers(table))
        return (end_program(table, ERR_JOIN), EXIT_FAILURE); */
    return (EXIT_SUCCESS);
}