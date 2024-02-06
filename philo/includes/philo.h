/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:21 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/06 18:23:27 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define PHILO_COUNT_MAX 200

# define USAGE "Usage->./philo number_of_philosophers \
	t_die t_eat t_sleep \
	[number_of_times_each_philosopher_must_eat](optional)\n"

# define MEMORY_ERR "Error:\nMemory allocation failed\n"
# define ARGS_ERR "Error:\nInvalid arguments\n"
# define MUTEX_ERR "Error:\nMutex initialization failed\n"
# define THREAD_CREATE_ERR "Error:\nThread creation failed\n"
# define THREAD_JOIN_ERR "Error:\nThread join failed\n"
# define GETTIME_ERR "Error:\nGet actual time failed\n"

/* Philosophers's activities */
# define DEAD "died\n"
# define EAT "is eating\n"
# define FORK "has taken a fork\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define ALL_EATEN_MEALS "%09lld All philosophers has eaten their %d meals\n"
# define ALL_EATEN_MEAL "%09lld All philosophers has eaten their %d meal\n"

struct	s_program;

typedef struct s_config
{
	int					philo_count;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					meals_count;
	long long int		start_time;
	int					stop;
	pthread_mutex_t		mutex_console;
	pthread_mutex_t		mutex_eat;
	pthread_mutex_t		mutex_stop;
	struct s_program	*program;
}	t_config;

typedef struct s_philo
{
	int				pos;
	int				meals_count;
	int				is_eating;
	int				is_dead;
	long long int	t_meal;
	int				stop;
	pthread_t		thread;
	pthread_mutex_t	mutex_t_meal;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_config		*config;
}	t_philo;

typedef struct s_program
{
	t_config		config;
	t_philo			*philos;
}	t_program;

// EXIT
void			ft_exit(t_program *program, char *error, int mutex, int thread);
int				destroy_thread(t_program *program, int count);
int				destroy_mutex(t_program *program, int count);

// INIT
int				init(t_program *program, int ac, char **av);

// PHILO
int				check_all_eaten(t_program *program);;
int				check_philo_died(t_config *config);
void			*set_philo_stop(t_philo *philo);
int				philo_start(t_program *program);

// MONITORING
void			*monitoring(void *void_program);

// ACTIVITIES
int				go_eat(t_philo *philo);
int				go_sleep(t_philo *philo);
int				go_think(t_philo *philo);

// UTILS
int				check_args(const char *str);
void			ft_print_state(t_philo *philo, char *str);
void			ft_usleep(long int time_in_ms, t_program *program);
long long int	get_timestamp(void);

// LIBFT
void			ft_putstr_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
void			ft_putchar_fd(char c, int fd);

#endif
