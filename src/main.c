/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:45 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/27 19:50:45 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	char	*status;

	status = NULL;
	table = malloc(sizeof(t_table));
	if (!table)
		return (end_program(table, ERR_MALLOC), EXIT_FAILURE);
	table->stop = false;
    table->philos = NULL;
	if (argc < 5 || argc > 6)
		return (end_program(table, ERR_ARGC), EXIT_FAILURE);
	if (!check_args(argc, argv))
		return (end_program(table, ERR_ARGV), EXIT_FAILURE);
	if (!init_table(table, argc, argv, &status))
		return (end_program(table, status), EXIT_FAILURE);
	if (!create_philosophers(table))
		return (end_program(table, ERR_THREAD), EXIT_FAILURE);
	// if (!join_philosophers(table))
	// 	return (end_program(table, ERR_JOIN), EXIT_FAILURE);
    observer(table);
	return (end_program(table, NULL), EXIT_SUCCESS);
}
