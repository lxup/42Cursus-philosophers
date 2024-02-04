/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:03:58 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/04 23:31:56 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->config->is_dead)
	{
		ft_print_state(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		ft_print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_state(philo, "has taken a fork");
		ft_print_state(philo, "is eating");
		ft_usleep(philo->config->t_eat, philo->config);
		philo->t_meal = get_timestamp();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (!philo->config->is_dead)
			philo->eat_count += 1;
		ft_print_state(philo, "is sleeping");
		ft_usleep(philo->config->t_sleep, philo->config);
	}
	return (0);
}

void	*check_death(void *args)
{
	t_philo	*philos;
	int		i;
	int		philos_has_eaten;

	philos = (t_philo *)args;
	while (!philos->config->is_dead)
	{
		i = -1;
		philos_has_eaten = 0;
		while (++i < philos->config->philo_count)
		{
			if (get_timestamp() - (philos + i)->t_meal > philos->config->t_die)
			{
				ft_print_state(philos + i, "died");
				philos->config->is_dead = 1;
				break ;
			}
			if (philos->config->eat_count != -1 && \
				(philos + i)->eat_count >= philos->config->eat_count)
				philos_has_eaten++;
		}
		if (philos_has_eaten == philos->config->philo_count)
			philos->config->is_dead = 1;
	}
	return (0);
}

void	philo_start(t_philo *philos)
{
	int	i;

	i = -1;
	philos->config->start_time = get_timestamp();
	while (++i < philos->config->philo_count)
	{
		(philos + i)->t_meal = get_timestamp();
		if (pthread_create(&(philos + i)->thread, NULL, \
			&philo_life, philos + i))
			ft_error(THREAD_CREATE_ERR, NULL, 0);
		pthread_detach((philos + i)->thread);
		usleep(50);
	}
	if (pthread_create(&philos->config->check_death, NULL, \
		&check_death, philos))
		ft_error(THREAD_CREATE_ERR, NULL, 0);
	if (pthread_join(philos->config->check_death, NULL))
		ft_error(THREAD_JOIN_ERR, NULL, 0);
	ft_destroy_mutex_array(philos->config->mutex_fork, \
		philos->config->fork_count);
	pthread_mutex_destroy(&philos->config->mutex_console);
}

void	ft_free(t_philo *philo, t_config *config, pthread_mutex_t *forks)
{
	if (forks)
		free(forks);
	if (config)
		free(config);
	if (philo)
		free(philo);
}

int	main(int ac, char **av)
{
	t_philo		*philos;

	if (ac < 5 || ac > 6)
		return (ft_error(ARGS_ERR, NULL, 1), EXIT_FAILURE);
	if (!init(&philos, ac, av))
		return (EXIT_FAILURE);
	philo_start(philos);
	return (EXIT_SUCCESS);
}
