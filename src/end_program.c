/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:23 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/26 21:19:17 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Checks if the philosopher has died by calculating
// the time passed since last meal. It returns true if the time is greater
// than the time allowed to pass without eating, else it returns false.
bool	death_watcher(t_philo *philo, u_int64_t now)
{
	u_int64_t	time_to_die;
	u_int64_t	time_to_eat;
	u_int64_t	time_to_sleep;

	time_to_die = philo->table->input.time_to_die;
	time_to_eat = philo->table->input.time_to_eat;
	time_to_sleep = philo->table->input.time_to_sleep;
	pthread_mutex_lock(&philo->table->mutex[DEATH]);
	if (now - philo->last_meal > time_to_die && !philo->table->stop)
	{
		philo->table->stop = true;
		if ((time_to_die < time_to_eat) || (time_to_die < (time_to_eat
					+ time_to_sleep)))
			printf("%s%ld %ld %s%s", RED, time_to_die, philo->id, DIE, RESET);
		else
			printf("%s%ld %ld %s%s", RED, get_time() - philo->table->start_time,
				philo->id, DIE, RESET);
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
