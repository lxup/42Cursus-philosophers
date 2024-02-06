/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:24:42 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/06 20:02:09 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(const char *str)
{
	long int	n;

	while (*str == ' ' || *str == '\f' || *str == '\n' || \
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	n = 0;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		n = n * 10 + *str - '0';
		if (n > INT_MAX)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)n);
}

void	ft_print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->config->mutex_stop);
	if (philo->config->stop || check_all_eaten(philo->config->program))
	{
		pthread_mutex_unlock(&philo->config->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&philo->config->mutex_stop);
	pthread_mutex_lock(&philo->config->mutex_console);
	printf("%09lld %d %s", get_timestamp() - philo->config->start_time, \
		philo->pos, str);
	pthread_mutex_unlock(&philo->config->mutex_console);
}

void	ft_usleep(long int time_in_ms, t_program *program)
{
	long int	current_time;

	current_time = 0;
	current_time = get_timestamp();
	while ((get_timestamp() - current_time) < time_in_ms)
	{
		pthread_mutex_lock(&program->config.mutex_stop);
		if (program->config.stop)
		{
			pthread_mutex_unlock(&program->config.mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&program->config.mutex_stop);
		usleep(time_in_ms / 10);
	}
}

long long int	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
