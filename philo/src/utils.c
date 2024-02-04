/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:24:42 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/04 18:24:43 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int error, char *extra_msg, int show_usage)
{
	if (error)
		ft_putstr_fd("Error: ", 2);
	else
		ft_putstr_fd("Error\n", 2);
	if (error == MEMORY_ERR)
		ft_putstr_fd("Memory allocation failed", 2);
	if (error == ARGS_ERR)
		ft_putstr_fd("Invalid arguments", 2);
	if (error == MUTEX_ERR)
		ft_putstr_fd("Mutex initialization failed", 2);
	if (error == THREAD_CREATE_ERR)
		ft_putstr_fd("Thread creation failed", 2);
	if (error == THREAD_JOIN_ERR)
		ft_putstr_fd("Thread join failed", 2);
	ft_putstr_fd("\n", 2);
	if (extra_msg)
	{
		ft_putstr_fd(extra_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (show_usage)
		ft_putstr_fd("Usage: ./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat](optional)\n", 2);
	return (0);
}

void	ft_print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->config->mutex_console));
	if (!philo->config->is_dead)
		printf("%09lld %d %s\n", \
			get_timestamp() - philo->config->start_time, philo->pos, str);
	pthread_mutex_unlock(&(philo->config->mutex_console));
}

void	ft_usleep(long long time_in_ms, t_config *config)
{
	long long	t;

	t = get_timestamp();
	while (!config->is_dead)
	{
		if (get_timestamp() - t >= time_in_ms)
			break ;
		usleep(500);
	}
}

long long int	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
