/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:23 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/29 01:26:15 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Checks if the philosopher has died by calculating the time passed
// since last meal. Also checks if all the philosophers have eaten.
bool	death_watcher(t_philo *philo, u_int64_t now)
{
	u_int64_t	t_last_meal;
	bool		is_program_over;
	bool		is_philo_full;

	pthread_mutex_lock(&philo->table->mutex[EATING]);
	is_philo_full = (int)philo->nb_eat == philo->table->input.nb_eat;
	t_last_meal = now - philo->last_meal;
	pthread_mutex_unlock(&philo->table->mutex[EATING]);
	pthread_mutex_lock(&philo->table->mutex[DEATH]);
	is_program_over = philo->table->stop;
	pthread_mutex_unlock(&philo->table->mutex[DEATH]);
	if (is_philo_full && !philo->is_done)
	{
		philo->is_done = true;
		return (philo->table->philo_full++, true);
	}
	if ((t_last_meal > philo->table->input.time_to_die) && !is_program_over)
	{
		ft_printf(philo, DIE, RED);
		pthread_mutex_lock(&philo->table->mutex[DEATH]);
		philo->table->stop = true;
		return (pthread_mutex_unlock(&philo->table->mutex[DEATH]), true);
	}
	return (false);
}

// Destroys the mutexes of each philosopher and the global mutexes.
static void	destroy_mutexes(t_table *table)
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
			destroy_mutexes(table);
		if (table->philos)
			free(table->philos);
		free(table);
		if (error)
		{
			write(2, error, ft_strlen(error));
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}
