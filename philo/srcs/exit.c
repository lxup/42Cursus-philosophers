/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:50:47 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/05 22:39:50 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_thread(t_program *program, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		pthread_mutex_destroy(&program->philos[i].left_fork);
		pthread_mutex_destroy(&program->philos[i].mutex_t_meal);
		pthread_mutex_destroy(&program->philos[i].mutex_stop);
		pthread_join(program->philos[i].thread, NULL);
	}
	return (1);
}

int	destroy_mutex(t_program *program, int count)
{
	if (count == 3)
		pthread_mutex_destroy(&(program->config.mutex_stop));
	if (count >= 2)
		pthread_mutex_destroy(&(program->config.mutex_eat));
	if (count >= 1)
		pthread_mutex_destroy(&(program->config.mutex_console));
	return (1);
}

void	ft_exit(t_program *program, char *error, int mutex, int thread)
{
	if (error)
	{
		ft_putstr_fd(error, 2);
		if (ft_strncmp(error, ARGS_ERR, ft_strlen(error)) == 0)
			ft_putstr_fd(USAGE, 2);
	}
	if (mutex > 0)
		destroy_mutex(program, mutex);
	if (thread > 0)
		destroy_thread(program, thread);
	if (program->philos)
		free(program->philos);
}