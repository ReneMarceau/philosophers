/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:14 by rmarceau          #+#    #+#             */
/*   Updated: 2023/06/28 16:52:43 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* *************** ***************           *************** *************** */
/*                                  INCLUDES                                 */
/* *************** ***************           *************** *************** */

/* ***** THREADS AND MUTEX ***** */
# include <pthread.h>
/* ***** TO WRITE IN STDOUT ***** */
# include <stdio.h>
/* ***** DYNAMIC ALLOCATION ***** */
# include <stdlib.h>
/* ***** USLEEP ***** */
# include <unistd.h>
/* ***** TIME MANAGEMENT ***** */
# include <sys/time.h>
/* ***** TIME TYPE ***** */
# include <stdint.h>
/* ***** BOOLEAN TYPE ***** */
# include <stdbool.h>
/* ***** INT_MAX ***** */
# include <limits.h>

/* *************** ***************           *************** *************** */
/*                                   MACROS                                  */
/* *************** ***************           *************** *************** */

/* ***** ERRORS ***** */
# define ERR_ARGC "Error: wrong number of arguments(must be 4 or 5)\n"
# define ERR_ARGV "Error: wrong argument\n\
        1st argument: number of philosophers\n\
        2nd argument: time to die (in ms)\n\
        3rd argument: time to eat (in ms)\n\
        4th argument: time to sleep (in ms)\n\
        5th argument: number of times each philosopher must eat (optional)\n"
# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_MUTEX "Error: mutex creation failed\n"
# define ERR_THREAD "Error: thread creation failed\n"
# define ERR_JOIN "Error: thread join failed\n"

/* ***** MOVES ***** */
# define TAKE_FORK "has taken a fork 🍴\n"
# define EAT "is eating 🍝\n"
# define SLEEP "is sleeping 😴\n"
# define THINK "is thinking 💭\n"
# define DIE "died 💀\n"

/* ***** COLORS ***** */
# define RESET "\e[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

/* *************** ***************           *************** *************** */
/*                                   STRUCTS                                 */
/* *************** ***************           *************** *************** */

/* ***** MUTEXES ***** */
typedef enum e_mutexes
{
	WRITE,
    EATING,
	DEATH,
    GLOBAL,
	NB_MUTEXES
}					t_mutexes;

/* ***** INPUT ***** */
typedef struct s_input
{
	size_t			nb_philo;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				nb_eat;
}					t_input;

/* ***** PHILOSOPHERS ***** */
typedef struct s_philo
{
	size_t			id;
	size_t			nb_eat;
	u_int64_t		last_meal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
    bool            is_eating;
	struct s_table	*table;
}					t_philo;

/* ***** TABLE ***** */
typedef struct s_table
{
	t_input			input;
	u_int64_t		start_time;
	t_philo			*philos;
    size_t          philo_full;
	pthread_mutex_t	mutex[NB_MUTEXES];
	bool			stop;
}					t_table;

/* *************** ***************           *************** *************** */
/*                                 FUNCTIONS                                 */
/* *************** ***************           *************** *************** */

/* ***** PHILO_LIFE ***** */
void				*philo_life(void *arg);

/* ***** THREAD ***** */
void                observer(t_table *table);
bool				create_philosophers(t_table *table);
bool				join_philosophers(t_table *table);
bool				death_watcher(t_philo *philo, u_int64_t now);

/* ***** LIBFT  ***** */
bool				ft_printf(t_philo *philo, const char *string, char *color);
long				ft_atol(const char *string);
size_t				ft_strlen(const char *string);

/* ***** INIT ***** */
bool				init_table(t_table *table, int argc, char **argv,
						char **status);

/* ***** UTILS ***** */
void				end_program(t_table *table, char *error);
bool				check_args(int argc, char **argv);
u_int64_t			get_time(void);
void				ft_usleep(u_int64_t time);
void				drop_forks(t_philo *philo);

#endif