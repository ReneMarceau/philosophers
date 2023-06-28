/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:52 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/27 19:56:27 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Creates threads for each philosopher
// and assigns their last meal time to the start time of the table.
bool	create_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->input.nb_philo)
	{
		table->philos[i].last_meal = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL, &philo_life,
				&table->philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

// Waits for all philosopher threads to finish their tasks.
bool	join_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->input.nb_philo)
	{
		if (pthread_join(table->philos[i++].thread, NULL) != 0)
			return (false);
	}
	return (true);
}

void    observer(t_table *table)
{
    size_t  i;

    i = 0;
    while (true)
    {
        if (i == table->input.nb_philo)
            i = 0;
        if (!table->philos[i].is_eating)
            death_watcher(&table->philos[i], get_time());
        if (table->philo_full == table->input.nb_philo || table->stop || table->input.nb_eat == 0)
            break ;
        i++;
    }
}