/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:03:58 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/04 18:20:53 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_config *config, t_philo *philos, t_fork *forks, int error)
{
	int	i;

	i = -1;
	if (philos)
	{
		while (++i < config->philo_count)
		{
			pthread_mutex_destroy(&(philos[i].last_eat_mutex));
			pthread_mutex_destroy(&(philos[i].l_fork->mutex));
		}
		free(philos);
	}
	i = -1;
	if (forks)
		free(forks);
	pthread_mutex_destroy(&(config->dead_mutex));
	pthread_mutex_destroy(&(config->main_mutex));
	return (error);
}

int	main(int ac, char **av)
{
	t_config	config;
	t_philo		*philos;
	t_fork		*forks;
	int			exit_code;

	exit_code = EXIT_SUCCESS;
	if (!init_config(&config, ac, av))
		return (ft_exit(&config, NULL, NULL, EXIT_FAILURE));
	if (!init_philosophers(&philos, &forks, &config))
		return (ft_exit(&config, NULL, NULL, EXIT_FAILURE));
	if (!init_threads(&philos, &config))
		exit_code = kill_threads(&philos[0]);
	if (!wait_threads(&philos, &config))
		return (ft_exit(&config, philos, forks, EXIT_FAILURE));
	return (ft_exit(&config, philos, forks, exit_code));
}
