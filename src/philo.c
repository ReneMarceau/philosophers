/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:47 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/27 19:54:11 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
    philo->is_eating = true;
	ft_usleep(philo->table->input.time_to_eat);
    philo->last_meal = get_time();
    philo->is_eating = false;
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
        ft_printf(philo, TAKE_FORK, YELLOW);
		ft_usleep(philo->table->input.time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
    {
        ft_printf(philo, THINK, MAGENTA);
		ft_usleep(philo->table->input.time_to_eat / 2);
    }
	while (true)
	{
		if (!philo_eating(philo) || !philo_sleeping(philo) || !ft_printf(philo, THINK, MAGENTA))
			break ;
	}
	return (NULL);
}
