/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:21 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/04 21:44:23 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include "../libft/libft.h"

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define PHILO_COUNT_MAX 200

enum	e_errors
{
	MEMORY_ERR			= -1,
	ARGS_ERR			= -2,
	MUTEX_ERR			= -3,
	THREAD_CREATE_ERR	= -4,
	THREAD_JOIN_ERR		= -5,
};

typedef struct s_config
{
	int				philo_count;
	int				fork_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long long int	start_time;
	int				is_dead;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_console;
	pthread_t		check_death;
}	t_config;

typedef struct s_philo
{
	int				pos;
	int				eat_count;
	long long int	time_last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_config		*config;
}	t_philo;

// INITS
int				init(t_philo **philos, int ac, char **av);

// UTILS
int				ft_error(int error, char *extra_msg, int show_usage);
void			ft_print_state(t_philo *philo, char *str);
void			ft_usleep(long long time_in_ms, t_config *config);
long long int	get_timestamp(void);

#endif
