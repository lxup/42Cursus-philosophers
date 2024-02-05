/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:03:58 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 22:46:00 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_philos(t_program *program)
{
	int		i;
	int		philos_stopped;

	philos_stopped = 0;
	i = -1;
	while (++i < program->config.philo_count)
	{
		pthread_mutex_lock(&program->philos[i].mutex_stop);
		if (program->philos[i].stop)
			philos_stopped++;
		pthread_mutex_unlock(&program->philos[i].mutex_stop);
	}
	if (philos_stopped == program->config.philo_count)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program	program;

	if (ac < 5 || ac > 6)
		return (ft_exit(&program, ARGS_ERR, 0, 0), EXIT_FAILURE);
	if (!init(&program, ac, av))
		return (EXIT_FAILURE);
	if (!philo_start(&program))
		return (EXIT_FAILURE);
	while (1)
	{
		usleep(5000);
		if (stop_philos(&program))
			break ;
	}
	return (ft_exit(&program, NULL, 3, program.config.philo_count), EXIT_SUCCESS);
}
