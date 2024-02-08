/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:51:18 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/08 18:42:47 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_eaten(t_program *program)
{
	int		i;
	int		philos_has_eaten;

	if (program->config.meals_count == -1)
		return (0);
	philos_has_eaten = 0;
	i = -1;
	while (++i < program->config.philo_count)
	{
		pthread_mutex_lock(&program->config.mutex_eat);
		if (program->philos[i].meals_count >= program->config.meals_count)
			philos_has_eaten++;
		pthread_mutex_unlock(&program->config.mutex_eat);
	}
	if (philos_has_eaten == program->config.philo_count)
		return (1);
	return (0);
}

int	check_philo_died(t_config *config)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&config->mutex_stop);
	if (config->stop)
		result = 1;
	pthread_mutex_unlock(&config->mutex_stop);
	return (result);
}

void	*set_philo_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex_stop));
	philo->stop = 1;
	pthread_mutex_unlock(&(philo->mutex_stop));
	return (NULL);
}

static void	*philo_life(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->pos % 2 == 0)
		ft_usleep(philo->config->t_eat / 10, philo->config->program);
	while (!check_philo_died(philo->config))
	{
		if (!go_eat(philo))
			return (NULL);
		if (!go_sleep(philo))
			return (NULL);
		if (!go_think(philo))
			return (NULL);
	}
	return (set_philo_stop(philo));
}

int	philo_start(t_program *program)
{
	int			i;
	pthread_t	t_monitoring;

	i = -1;
	while (++i < program->config.philo_count)
	{
		if (pthread_create(&(program->philos[i].thread), NULL, \
			philo_life, &program->philos[i]))
			return (ft_exit(program, THREAD_CREATE_ERR, 3, i), 0);
	}
	pthread_create(&t_monitoring, NULL, monitoring, program);
	pthread_join(t_monitoring, NULL);
	return (1);
}
