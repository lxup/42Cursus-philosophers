/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:14:48 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 19:48:57 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_life(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	ft_print_state(ph, "has taken a fork");
	if (!ph->right_fork)
	{
		ft_usleep(ph->config->start_time * 2);
		return ;
	}
	pthread_mutex_lock(ph->right_fork);
	ft_print_state(ph, "has taken a fork");
	ft_print_state(ph, "is eating");
	pthread_mutex_lock(&ph->config->mutex_t_eat);
	ph->t_meal = get_timestamp();
	pthread_mutex_unlock(&ph->config->mutex_t_eat);
	ft_usleep(ph->config->t_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	ft_print_state(ph, "is sleeping");
	ft_usleep(ph->config->t_sleep);
	ft_print_state(ph, "is thinking");
}

int	check_death(t_philo *philo, int is_stop)
{
	pthread_mutex_lock(&philo->config->mutex_is_stop);
	if (is_stop)
		philo->config->stop = is_stop;
	if (philo->config->stop)
	{
		pthread_mutex_unlock(&philo->config->mutex_is_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->config->mutex_is_stop);
	return (0);
}

void	*is_dead(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->config->t_die + 1);
	pthread_mutex_lock(&philo->config->mutex_t_eat);
	pthread_mutex_lock(&philo->config->mutex_finish);
	if (!check_death(philo, 0) && !philo->finish
		&& ((get_timestamp() - philo->t_meal) \
		>= (long)(philo->config->t_die)))
	{
		pthread_mutex_unlock(&philo->config->mutex_t_eat);
		pthread_mutex_unlock(&philo->config->mutex_finish);
		ft_print_state(philo, "died");
		return (check_death(philo, 1), NULL);
	}
	pthread_mutex_unlock(&philo->config->mutex_t_eat);
	pthread_mutex_unlock(&philo->config->mutex_finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->pos % 2 == 0)
		ft_usleep(philo->config->t_eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death, NULL, is_dead, philo);
		philo_life(philo);
		pthread_detach(philo->thread_death);
		if ((int)++philo->eat_count == philo->config->eat_count)
		{
			pthread_mutex_lock(&philo->config->mutex_finish);
			philo->finish = 1;
			philo->config->finish_count++;
			if (philo->config->finish_count == philo->config->philo_count)
			{
				pthread_mutex_unlock(&philo->config->mutex_finish);
				return (check_death(philo, 1), NULL);
			}
			pthread_mutex_unlock(&philo->config->mutex_finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	philo_start(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->config.philo_count)
	{
		if (pthread_create(&program->philos[i].thread, \
			NULL, thread, &program->philos[i]))
		{
			while (--i >= 0)
				pthread_join(program->philos[i].thread, NULL);
			return (ft_error(THREAD_CREATE_ERR, 0));
		}
	}
	return (1);
}
