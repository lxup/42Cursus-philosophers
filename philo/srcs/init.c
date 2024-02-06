/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:24:34 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/06 15:42:49 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_philo(t_philo *philo)
{
	if (pthread_mutex_init(&philo->left_fork, NULL))
		return (pthread_mutex_destroy(&philo->left_fork), 0);
	if (pthread_mutex_init(&philo->mutex_stop, NULL))
		return (pthread_mutex_destroy(&philo->left_fork), \
		pthread_mutex_destroy(&philo->mutex_stop), 0);
	if (pthread_mutex_init(&philo->mutex_t_meal, NULL))
		return (pthread_mutex_destroy(&philo->left_fork), \
		pthread_mutex_destroy(&philo->mutex_stop), \
		pthread_mutex_destroy(&philo->mutex_t_meal), 0);
	return (1);
}

static int	init_config(t_program *program, int ac, char **av)
{
	program->config.philo_count = check_args(av[1]);
	program->config.t_die = check_args(av[2]);
	program->config.t_eat = check_args(av[3]);
	program->config.t_sleep = check_args(av[4]);
	program->config.meals_count = -1;
	if (ac == 6)
		program->config.meals_count = check_args(av[5]);
	if (program->config.philo_count < 1 \
		|| program->config.philo_count > PHILO_COUNT_MAX \
		|| program->config.t_die <= 0 || program->config.t_eat <= 0 \
		|| program->config.t_sleep <= 0 \
		|| (ac == 6 && program->config.meals_count <= 0))
		return (ft_exit(program, ARGS_ERR, 0, 0), 0);
	program->config.start_time = -1;
	program->config.stop = 0;
	program->config.program = program;
	return (1);
}

static int	init_mutex(t_program *program)
{
	if (pthread_mutex_init(&program->config.mutex_console, NULL))
		return (ft_exit(program, MUTEX_ERR, 1, 0), 0);
	if (pthread_mutex_init(&program->config.mutex_eat, NULL))
		return (ft_exit(program, MUTEX_ERR, 2, 0), 0);
	if (pthread_mutex_init(&program->config.mutex_stop, NULL))
		return (ft_exit(program, MUTEX_ERR, 3, 0), 0);
	return (1);
}

static int	init_philos(t_program *program)
{
	int	i;

	i = -1;
	program->config.start_time = get_timestamp();
	while (++i < program->config.philo_count)
	{
		program->philos[i].config = &program->config;
		program->philos[i].pos = i + 1;
		program->philos[i].t_meal = program->config.start_time;
		program->philos[i].is_eating = 0;
		program->philos[i].is_dead = 0;
		program->philos[i].meals_count = 0;
		program->philos[i].stop = 0;
		program->philos[i].right_fork = NULL;
		if (!init_mutex_philo(&program->philos[i]))
			return (ft_exit(program, MUTEX_ERR, 3, i - 1), 0);
		if (i == program->config.philo_count - 1)
			program->philos[i].right_fork = &program->philos[0].left_fork;
		else
			program->philos[i].right_fork = &program->philos[i + 1].left_fork;
	}
	return (1);
}

int	init(t_program *program, int ac, char **av)
{
	if (!init_config(program, ac, av))
		return (0);
	program->philos = (t_philo *)malloc(sizeof(t_philo) \
		* program->config.philo_count);
	if (!program->philos)
		return (ft_exit(program, MEMORY_ERR, 0, 0), 0);
	if (!init_mutex(program))
		return (0);
	if (!init_philos(program))
		return (0);
	return (1);
}
