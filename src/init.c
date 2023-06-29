/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:40 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/29 01:26:30 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initializes the table struct with input values provided through command line
static bool	init_args(t_table *table, int argc, char **argv)
{
	table->input.nb_philo = ft_atol(argv[1]);
	if (table->input.nb_philo <= 0)
		return (false);
	table->input.time_to_die = ft_atol(argv[2]);
	table->input.time_to_eat = ft_atol(argv[3]);
	table->input.time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->input.nb_eat = ft_atol(argv[5]);
	else
		table->input.nb_eat = -1;
	return (true);
}

// Initializes all the mutexes required for the program
static bool	init_mutexes(t_table *table)
{
	size_t	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->input.nb_philo);
	if (!table->philos)
		return (false);
	while (i < table->input.nb_philo)
	{
		if (pthread_mutex_init(&table->philos[i++].left_fork, NULL) != 0)
			return (false);
	}
	i = 0;
	while (i < NB_MUTEXES)
	{
		if (pthread_mutex_init(&table->mutex[i++], NULL) != 0)
			return (false);
	}
	return (true);
}

// Initializes the philosopher threads with their respective attributes.
static void	init_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->input.nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_eat = 0;
		table->philos[i].is_eating = false;
		table->philos[i].is_done = false;
		table->philos[i].right_fork = &table->philos[(i + 1)
			% table->input.nb_philo].left_fork;
		table->philos[i].table = table;
		i++;
	}
}

// Initializes the table struct with initial values and mutexes.
bool	init_table(t_table *table, int argc, char **argv, char **status)
{
	table->philo_full = 0;
	if (!init_args(table, argc, argv))
		return (*status = ERR_ARGV, false);
	if (table->input.nb_eat == 0)
		return (false);
	if (!init_mutexes(table))
		return (*status = ERR_MUTEX, false);
	init_philosophers(table);
	return (true);
}
