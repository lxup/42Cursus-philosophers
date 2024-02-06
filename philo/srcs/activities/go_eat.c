/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:33:11 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/06 18:33:01 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	go_eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	ft_print_state(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	ft_print_state(philo, FORK);
	ft_print_state(philo, EAT);
	pthread_mutex_lock(&philo->mutex_t_meal);
	philo->t_meal = get_timestamp();
	pthread_mutex_unlock(&philo->mutex_t_meal);
	pthread_mutex_lock(&philo->config->mutex_eat);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->config->mutex_eat);
	ft_usleep(philo->config->t_eat, philo->config->program);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	go_eat_odd(t_philo *philo)
{
	if (philo->config->philo_count == 1)
		return (0);
	pthread_mutex_lock(philo->right_fork);
	ft_print_state(philo, FORK);
	pthread_mutex_lock(&philo->left_fork);
	ft_print_state(philo, FORK);
	ft_print_state(philo, EAT);
	pthread_mutex_lock(&philo->mutex_t_meal);
	philo->t_meal = get_timestamp();
	pthread_mutex_unlock(&philo->mutex_t_meal);
	pthread_mutex_lock(&philo->config->mutex_eat);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->config->mutex_eat);
	ft_usleep(philo->config->t_eat, philo->config->program);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (1);
}

int	go_eat(t_philo *philo)
{
	if (check_philo_died(philo->config) \
		|| check_all_eaten(philo->config->program))
		return (set_philo_stop(philo), 0);
	if (philo->pos % 2 == 0)
		go_eat_even(philo);
	else
		if(!go_eat_odd(philo))
			return (set_philo_stop(philo), 0);
	return (1);
}
