/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:47 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/25 21:01:22 by rmarceau         ###   ########.fr       */
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

// Releases both the forks held by the philosopher.
static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

// Executes the eating action of the philosopher.
// Locks the mutexes representing both forks and prints statements.
// Updates the last meal time of the philosopher
static bool	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (!ft_printf(philo, TAKE_FORK, YELLOW))
		return (pthread_mutex_unlock(&philo->left_fork), false);
	pthread_mutex_lock(philo->right_fork);
	if (!ft_printf(philo, TAKE_FORK, YELLOW))
		return (drop_forks(philo), false);
	if (!ft_printf(philo, EAT, GREEN))
		return (drop_forks(philo), false);
	philo->last_meal = get_time();
	ft_usleep(philo->table->input.time_to_eat);
	if (philo->table->input.nb_eat != -1)
		philo->nb_eat++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (true);
}

// Executes the sleeping action of the philosopher.
// It prints statements and sleeps for the duration specified in the input.
static bool	philo_sleeping(t_philo *philo)
{
	if (!ft_printf(philo, SLEEP, CYAN))
		return (false);
	ft_usleep(philo->table->input.time_to_sleep);
	return (true);
}

// This function is the life cycle of a philosopher thread.
// It first checks if there is only one philosopher, and if so,
// it waits for the time to pass out and dies.
// Otherwise, it begins executing its individual lifecycle by eating,
// sleeping and thinking.
void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->input.nb_philo == 1)
	{
		ft_usleep(philo->table->input.time_to_die);
		ft_printf(philo, DIE, RED);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		ft_printf(philo, THINK, MAGENTA);
		ft_usleep(philo->table->input.time_to_eat);
	}
	while ((int)philo->nb_eat != philo->table->input.nb_eat)
	{
		if (!philo_eating(philo) || !philo_sleeping(philo) || !ft_printf(philo,
				THINK, MAGENTA))
			return (NULL);
	}
	return (NULL);
}
