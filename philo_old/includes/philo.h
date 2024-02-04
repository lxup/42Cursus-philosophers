/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:21 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/04 18:24:07 by lquehec          ###   ########.fr       */
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
# define LONG_MIN -9223372036854775808
# define LONG_MAX 9223372036854775807

enum	e_errors
{
	MEMORY_ERR			= -1,
	ARGS_ERR			= -2,
};

typedef struct s_config
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long			start_time;
	int				dead_count;
	pthread_mutex_t	dead_mutex;
	pthread_t		dead_thread;
	pthread_mutex_t	main_mutex;
}	t_config;

typedef struct s_fork
{
	int				in_use;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				pos;
	pthread_t		thread;
	long			time_last_eat;
	int				eat_count;
	pthread_mutex_t	last_eat_mutex;
	t_fork			*r_fork;
	int				is_rf_taken;
	t_fork			*l_fork;
	int				is_lf_taken;
	t_config		*config;	
}	t_philo;

// MAIN
int		ft_exit(t_config *config, t_philo *philos, t_fork *forks, int error);

// INIT
void	init_philo(t_philo *philo, t_fork **forks, t_config *config, int pos);
int		init_philosophers(t_philo **philos, t_fork **forks, t_config *config);
int		init_config(t_config *config, int ac, char **av);

// THREADS
int		init_threads(t_philo **philos, t_config *config);
int		wait_threads(t_philo **philos, t_config *config);
int		kill_threads(t_philo *philo);

// PHILO
int		is_philo_dead(t_philo *philo);
int		check_philo_death(t_philo *philo, long current_time);
void	*check_philos_state(void *data);
void	sleep_after_eating(t_philo *philo);
void	*philo_life(void *data);

// FORK
void	take_fork(char side_fork, t_philo *philo);
void	release_fork(char side_fork, t_philo *philo);

// ERROR
int		ft_error(int error, char *str);

// UTILS
int		ft_print_state(char *str, t_philo *philo);
void	ft_usleep(long int time_in_ms);
long	get_timestamp(void);

#endif
