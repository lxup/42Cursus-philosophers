/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:03:58 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 20:30:46 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death_state(t_program *program)
{
	pthread_mutex_lock(&program->config.mutex_is_stop);
	if (program->config.stop)
	{
		pthread_mutex_unlock(&program->config.mutex_is_stop);
		return (1);
	}
	pthread_mutex_unlock(&program->config.mutex_is_stop);
	return (0);
}

int	ft_finish(t_program *program, int exit_code)
{
	int	i;

	i = -1;
	while (!check_death_state(program))
		ft_usleep(1);
	while (exit_code == EXIT_SUCCESS && ++i < program->config.philo_count)
		pthread_join(program->philos[i].thread, NULL);
	pthread_mutex_destroy(&program->config.mutex_console);
	pthread_mutex_destroy(&program->config.mutex_finish);
	pthread_mutex_destroy(&program->config.mutex_is_stop);
	pthread_mutex_destroy(&program->config.mutex_t_eat);
	i = -1;
	while (++i < program->config.philo_count)
		pthread_mutex_destroy(&program->philos[i].left_fork);
	free(program->philos);
	return (exit_code);
}

int	main(int ac, char **av)
{
	t_program	program;

	if (ac < 5 || ac > 6)
		return (ft_error(ARGS_ERR, 1), EXIT_FAILURE);
	if (!init(&program, ac, av))
		return (EXIT_FAILURE);
	if (!philo_start(&program))
		return (ft_finish(&program, EXIT_FAILURE));
	return (ft_finish(&program, EXIT_SUCCESS));
}
