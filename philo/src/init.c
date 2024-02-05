/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:24:34 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 20:11:52 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_config(t_program *program, int ac, char **av)
{
	program->config.philo_count = check_args(av[1]);
	program->config.t_die = check_args(av[2]);
	program->config.t_eat = check_args(av[3]);
	program->config.t_sleep = check_args(av[4]);
	program->config.eat_count = -1;
	if (ac == 6)
		program->config.eat_count = check_args(av[5]);
	if (program->config.philo_count < 1 \
		|| program->config.philo_count > PHILO_COUNT_MAX \
		|| program->config.t_die <= 0 || program->config.t_eat <= 0 \
		|| program->config.t_sleep <= 0 \
		|| (ac == 6 && program->config.eat_count <= 0))
		return (ft_error(ARGS_ERR, 1));
	program->config.start_time = -1;
	program->config.finish_count = 0;
	program->config.stop = 0;
	return (1);
}

static int	init_mutex(t_program *program)
{
	if (pthread_mutex_init(&program->config.mutex_console, NULL))
		return (0);
	if (pthread_mutex_init(&program->config.mutex_finish, NULL))
		return (0);
	if (pthread_mutex_init(&program->config.mutex_is_stop, NULL))
		return (0);
	if (pthread_mutex_init(&program->config.mutex_t_eat, NULL))
		return (0);
	return (1);
}

static int	destroy_mutex(t_program *program)
{
	if (pthread_mutex_destroy(&program->config.mutex_console))
		return (0);
	if (pthread_mutex_destroy(&program->config.mutex_finish))
		return (0);
	if (pthread_mutex_destroy(&program->config.mutex_is_stop))
		return (0);
	if (pthread_mutex_destroy(&program->config.mutex_t_eat))
		return (0);
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
		program->philos[i].eat_count = 0;
		program->philos[i].t_meal = program->config.start_time;
		program->philos[i].finish = 0;
		program->philos[i].right_fork = NULL;
		if (pthread_mutex_init(&program->philos[i].left_fork, NULL))
			return (ft_destroy_mutex_array(program->philos, i), 0);
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
		return (ft_error(MEMORY_ERR, 0));
	if (!init_mutex(program))
		return (ft_error(MUTEX_ERR, 0));
	if (!init_philos(program))
		return (destroy_mutex(program), ft_error(MUTEX_ERR, 0));
	return (1);
}
