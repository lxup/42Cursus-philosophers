/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:52:25 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 23:26:41 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->mutex_stop);
	philo->config->stop = 1;
	pthread_mutex_unlock(&philo->config->mutex_stop);
	ft_print_state(philo, DEAD);
}

void	*monitoring(void *void_program)
{
	t_program	*program;
	int		i;

	program = (t_program *)void_program;
	while (!program->config.stop)
	{
		i = -1;
		while (++i < program->config.philo_count)
		{
			pthread_mutex_lock(&program->philos[i].mutex_t_meal);
			if (get_timestamp() - program->philos[i].t_meal >= program->config.t_die)
			{
				philo_died(&program->philos[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&program->philos[i].mutex_t_meal);
		}
		if (check_all_eaten(program))
			break ;
	}
	return (NULL);
}