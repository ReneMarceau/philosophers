/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:14:59 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/26 18:01:34 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Releases both the forks held by the philosopher.
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

// Returns the current time in milliseconds using both seconds and microseconds.
u_int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((u_int64_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

// Used to sleep the program for a given amount of time in milliseconds,
// by repeatedly checking the elapsed time since starting the sleep.
void	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time / 10);
}

// Checks if a string is a valid integer.
static bool	is_valid_arg(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] < '0' || string[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

// Checks if all command-line arguments are valid integers
// within the range of an integer variable.
bool	check_args(int argc, char **argv)
{
	long	argument;
	int		i;

	i = 0;
	while (++i < argc)
	{
		argument = ft_atol(argv[i]);
		if (!is_valid_arg(argv[i]) || argument > INT_MAX)
			return (false);
	}
	return (true);
}
