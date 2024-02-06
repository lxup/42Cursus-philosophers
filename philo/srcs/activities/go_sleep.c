/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:43:57 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/06 18:04:45 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_sleep(t_philo *philo)
{
	if (check_philo_died(philo->config) \
		|| check_all_eaten(philo->config->program))
		return (set_philo_stop(philo), 0);
	ft_print_state(philo, SLEEP);
	ft_usleep(philo->config->t_sleep, philo->config->program);
	return (1);
}
