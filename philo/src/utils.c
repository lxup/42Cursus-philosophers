/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:24:42 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 19:48:13 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex_array(t_philo *philos, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&philos[i].left_fork);
		i--;
	}
}

int	ft_error(int error, int show_usage)
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
	if (show_usage)
		ft_putstr_fd("Usage: ./philo number_of_philosophers "
			"t_die t_eat t_sleep "
			"[number_of_times_each_philosopher_must_eat](optional)\n", 2);
	return (0);
}

void	ft_print_state(t_philo *philo, char *str)
{
	long long int	current_time;

	current_time = -1;
	current_time = get_timestamp() - philo->config->start_time;
	pthread_mutex_lock(&(philo->config->mutex_console));
	if (current_time >= 0 && !check_death(philo, 0))
		printf("%09lld %d %s\n", \
			current_time, philo->pos, str);
	pthread_mutex_unlock(&(philo->config->mutex_console));
}

void	ft_usleep(long int time_in_ms)
{
	long int	current_time;

	current_time = 0;
	current_time = get_timestamp();
	while ((get_timestamp() - current_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

long long int	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_error(GETTIME_ERR, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
