/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:14:48 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 23:04:45 by lquehec          ###   ########.fr       */
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

// void	*thread(void *data)
// {
// 	t_philo					*philo;

// 	philo = (t_philo *)data;
// 	if (philo->pos % 2 == 0)
// 		ft_usleep(50);
// 	while (!check_death(philo, 0))
// 	{
// 		pthread_create(&philo->thread_death, NULL, is_dead, philo);
// 		philo_life(philo);
// 		pthread_detach(philo->thread_death);
// 		if ((int)++philo->eat_count == philo->config->eat_count)
// 		{
// 			pthread_mutex_lock(&philo->config->mutex_finish);
// 			philo->finish = 1;
// 			philo->config->finish_count++;
// 			if (philo->config->finish_count == philo->config->philo_count)
// 			{
// 				pthread_mutex_unlock(&philo->config->mutex_finish);
// 				return (check_death(philo, 1), NULL);
// 			}
// 			pthread_mutex_unlock(&philo->config->mutex_finish);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }

// int	philo_start(t_program *program)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < program->config.philo_count)
// 	{
// 		if (pthread_create(&program->philos[i].thread, NULL, thread, &program->philos[i]))
// 			return (ft_error(THREAD_CREATE_ERR, 0));
// 			// return (panic(ERR_THREAD, 3, data->n_philo, data));
// 	}
// 	// if (program->config.philo_count == 1)
// 	// {
// 	// 	pthread_create(&tid, NULL, monitoring_one, (void *)data);
// 	// 	pthread_join(tid, NULL);
// 	// }
// 	// else
// 	// {
// 	// 	pthread_create(&tid, NULL, monitoring, (void *)data);
// 	// 	pthread_join(tid, NULL);
// 	// }
// 	// while (++i < program->config.philo_count)
// 	// {
// 	// 	if (pthread_create(&program->philos[i].thread, \
// 	// 		NULL, thread, &program->philos[i]))
// 	// 	{
// 	// 		while (--i >= 0)
// 	// 			pthread_join(program->philos[i].thread, NULL);
// 	// 		return (ft_error(THREAD_CREATE_ERR, 0));
// 	// 	}
// 	// }
// 	return (1);
// }
