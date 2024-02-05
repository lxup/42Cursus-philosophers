/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:21 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 20:12:14 by lquehec          ###   ########.fr       */
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
	GETTIME_ERR			= -6,
};

typedef struct s_config
{
	int				philo_count;
	int				t_die;
	int				t_eat;
	pthread_mutex_t	mutex_t_eat;
	int				t_sleep;
	int				eat_count;
	long long int	start_time;
	pthread_mutex_t	mutex_console;
	int				finish_count;
	pthread_mutex_t	mutex_finish;
	int				stop;
	pthread_mutex_t	mutex_is_stop;
}	t_config;

typedef struct s_philo
{
	int				pos;
	int				eat_count;
	long long int	t_meal;
	pthread_t		thread;
	pthread_t		thread_death;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	int				finish;
	t_config		*config;
}	t_philo;

typedef struct s_program
{
	t_config		config;
	t_philo			*philos;
}	t_program;

// MAIN
int				ft_finish(t_program *program, int exit_code);

// PHILO
int				philo_start(t_program *program);
int				check_death(t_philo *philo, int is_stop);

// INITS
int				init(t_program *program, int ac, char **av);

// PARSING
int				check_args(const char *str);

// UTILS
void			ft_destroy_mutex_array(t_philo *philos, int i);
int				ft_error(int error, int show_usage);
void			ft_print_state(t_philo *philo, char *str);
void			ft_usleep(long int time_in_ms);
long long int	get_timestamp(void);

#endif
