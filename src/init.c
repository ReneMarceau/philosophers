/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:40 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/25 21:03:55 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initializes the table struct with input values provided through command line
// using the ft_atol() function.
static void	init_args(t_table *table, int argc, char **argv)
{
	table->input.nb_philo = ft_atol(argv[1]);
	table->input.time_to_die = ft_atol(argv[2]);
	table->input.time_to_eat = ft_atol(argv[3]);
	table->input.time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->input.nb_eat = ft_atol(argv[5]);
	else
		table->input.nb_eat = -1;
}

// Initializes all the mutexes required for the program
// and returns true upon successful initialization.
static bool	init_mutexes(t_table *table, char **status)
{
	size_t	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->input.nb_philo);
	if (!table->philos)
		return (*status = ERR_MALLOC, false);
	while (i < table->input.nb_philo)
	{
		if (pthread_mutex_init(&table->philos[i++].left_fork, NULL) != 0)
		{
			table->stop = true;
			return (*status = ERR_MUTEX, false);
		}
	}
	i = 0;
	while (i < NB_MUTEXES)
	{
		if (pthread_mutex_init(&table->mutex[i++], NULL) != 0)
		{
			table->stop = true;
			return (*status = ERR_MUTEX, false);
		}
	}
	return (true);
}

// Initializes the philosopher threads with their respective attributes.
static bool	init_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->input.nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_eat = 0;
		table->philos[i].right_fork = &table->philos[(i + 1)
			% table->input.nb_philo].left_fork;
		table->philos[i].table = table;
		i++;
	}
	return (true);
}

// Initializes the table struct with initial values and mutexes.
bool	init_table(t_table *table, int argc, char **argv, char **status)
{
	table->philos = NULL;
	init_args(table, argc, argv);
	if (!init_mutexes(table, status))
		return (false);
	init_philosophers(table);
	return (true);
}
