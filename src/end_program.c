/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:23 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/26 18:16:39 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Checks if the philosopher has died by calculating
// the time passed since last meal. It returns true if the time is greater
// than the time allowed to pass without eating, else it returns false.
bool	death_watcher(t_philo *philo, u_int64_t now)
{
	pthread_mutex_lock(&philo->table->mutex[DEATH]);
	if (now - philo->last_meal > philo->table->input.time_to_die)
	{
		pthread_mutex_unlock(&philo->table->mutex[DEATH]);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->mutex[DEATH]);
	return (false);
}

// Destroys the mutexes of each philosopher and the global mutexes.
void	destroy_mutexes(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->input.nb_philo)
		pthread_mutex_destroy(&table->philos[i++].left_fork);
	i = 0;
	while (i < NB_MUTEXES)
		pthread_mutex_destroy(&table->mutex[i++]);
}

// Ends the program with an exit status.
void	end_program(t_table *table, char *error)
{
	if (table)
	{
		if (table->stop)
		{
			destroy_mutexes(table);
			if (table->philos)
				free(table->philos);
		}
		free(table);
		if (error)
		{
			write(2, error, ft_strlen(error));
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}
