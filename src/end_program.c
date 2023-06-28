/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:23 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/28 17:13:52 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// This function checks if the program is over by checking two conditions:
// If the philosopher has eaten the required number of times (nb_eat).
// Otherwise, it checks if the time passed
// since the last meal is greater than the allowed time to die.
// If it is, then it sets the table stop flag to true
// and prints a message indicating the philosopher has died.
static bool is_program_over(t_philo *philo, u_int64_t now)
{
    bool is_program_over;
    bool is_philo_full;
    u_int64_t time_since_last_meal;

    pthread_mutex_lock(&philo->table->mutex[EATING]);
    is_philo_full = (int)philo->nb_eat == philo->table->input.nb_eat;
    time_since_last_meal = now - philo->last_meal;
    pthread_mutex_unlock(&philo->table->mutex[EATING]);
    pthread_mutex_lock(&philo->table->mutex[DEATH]);
    is_program_over = philo->table->stop || is_philo_full;
    pthread_mutex_unlock(&philo->table->mutex[DEATH]);
    if (is_program_over)
    {
        if (is_philo_full)
            philo->table->philo_full++;
        //pthread_mutex_unlock(&philo->table->mutex[DEATH]);
        return (true);
    }
	if (time_since_last_meal > philo->table->input.time_to_die && !is_program_over)
	{
        ft_printf(philo, DIE, RED);
        pthread_mutex_lock(&philo->table->mutex[DEATH]);
        philo->table->stop = true;
        pthread_mutex_unlock(&philo->table->mutex[DEATH]);
		return (true);
	}
    return (false);
}

// Checks if the philosopher has died by calculating
// the time passed since last meal. It returns true if the time is greater
// than the time allowed to pass without eating, else it returns false.
bool	death_watcher(t_philo *philo, u_int64_t now)
{
	//pthread_mutex_lock(&philo->table->mutex[DEATH]);
    if (is_program_over(philo, now))
        return (true);
	//pthread_mutex_unlock(&philo->table->mutex[DEATH]);
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
