/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:45:19 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/06 18:04:50 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_think(t_philo *philo)
{
	if (check_philo_died(philo->config) \
		|| check_all_eaten(philo->config->program))
		return (set_philo_stop(philo), 0);
	ft_print_state(philo, THINK);
	if (philo->config->philo_count % 2 != 0)
		ft_usleep(philo->config->t_eat / 10, philo->config->program);
	return (1);
}
