/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:42 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/27 18:31:22 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Calculates the length of a string.
size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

// Converts a string into a long integer.
long	ft_atol(const char *string)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*string == ' ' || (*string >= '\t' && *string <= '\r'))
		string++;
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			sign = -1;
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		result = result * 10 + (*string - '0');
		string++;
	}
	return (result * sign);
}

// Prints messages related to the actions of philosophers
// and returns a boolean value.
bool	ft_printf(t_philo *philo, const char *string, char *color)
{
	u_int64_t	now;

	pthread_mutex_lock(&philo->table->mutex[WRITE]);
	now = get_time() - philo->table->start_time;
	if (death_watcher(philo, get_time()))
	{
		pthread_mutex_unlock(&philo->table->mutex[WRITE]);
		return (false);
	}
	if (!philo->table->stop)
		printf("%s%llu %ld %s%s", color, now, philo->id, string, RESET);
	pthread_mutex_unlock(&philo->table->mutex[WRITE]);
	return (true);
}
