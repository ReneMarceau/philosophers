/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:45 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/29 13:33:58 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Observes constantly the philosophers to check if one of them died.
// Or if all of them have eaten.
static void	observer(t_table *table)
{
	bool	is_philo_eating;
	size_t	i;

	i = 0;
	while (true)
	{
		if (i == table->input.nb_philo)
			i = 0;
		pthread_mutex_lock(&table->mutex[EATING]);
		is_philo_eating = table->philos[i].is_eating;
		pthread_mutex_unlock(&table->mutex[EATING]);
		if (i == table->input.nb_philo)
			i = 0;
		pthread_mutex_lock(&table->mutex[DEATH]);
		table->stop = table->philo_full == table->input.nb_philo;
		pthread_mutex_unlock(&table->mutex[DEATH]);
		if (!is_philo_eating)
			death_watcher(&table->philos[i], get_time());
		if (table->stop)
			break ;
		i++;
		ft_usleep(3);
	}
}

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
	observer(table);
	if (!join_philosophers(table))
		return (end_program(table, ERR_JOIN), EXIT_FAILURE);
	return (end_program(table, NULL), EXIT_SUCCESS);
}
