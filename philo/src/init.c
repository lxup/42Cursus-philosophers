/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:24:34 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/04 23:31:56 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(const char *str)
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

static int	init_config(t_config **config, int ac, char **av)
{
	t_config	*new_config;

	new_config = (t_config *)malloc(sizeof(t_config));
	if (!new_config)
		return (ft_error(MEMORY_ERR, NULL, 0));
	new_config->philo_count = check_args(av[1]);
	new_config->fork_count = new_config->philo_count;
	new_config->t_die = check_args(av[2]);
	new_config->t_eat = check_args(av[3]);
	new_config->t_sleep = check_args(av[4]);
	if (new_config->philo_count < 1 \
		|| new_config->philo_count > PHILO_COUNT_MAX \
		|| new_config->t_die <= 0 || new_config->t_eat == -1 \
		|| new_config->t_sleep == -1)
		return (free(new_config), ft_error(ARGS_ERR, NULL, 1));
	new_config->eat_count = -1;
	if (ac == 6)
	{
		new_config->eat_count = check_args(av[5]);
		if (new_config->eat_count == -1)
			return (free(new_config), ft_error(ARGS_ERR, NULL, 1));
	}
	new_config->is_dead = 0;
	*config = new_config;
	return (1);
}

static int	init_fork(t_config *config)
{
	int	i;

	config->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* config->fork_count);
	if (!config->mutex_fork)
		return (ft_error(MEMORY_ERR, NULL, 0));
	i = -1;
	while (++i < config->fork_count)
	{
		if (pthread_mutex_init(config->mutex_fork + i, NULL))
			return (ft_destroy_mutex_array(config->mutex_fork, i - 1), \
				ft_free(NULL, config, config->mutex_fork), \
				ft_error(MUTEX_ERR, NULL, 0));
	}
	return (1);
}

static void	init_philo(t_philo *philo, int i, \
		t_config *config, pthread_mutex_t *forks)
{
	philo->pos = i + 1;
	philo->config = config;
	philo->eat_count = 0;
	philo->t_meal = 0;
	if (i == 0)
	{
		philo->left_fork = forks + config->philo_count - 1;
		philo->right_fork = forks + i;
	}
	else
	{
		philo->left_fork = forks + i - 1;
		philo->right_fork = forks + i;
	}
}

int	init(t_philo **philos, int ac, char **av)
{
	t_config	*config;
	t_philo		*new_philos;
	int			i;

	if (!init_config(&config, ac, av))
		return (0);
	if (pthread_mutex_init(&(config->mutex_console), NULL))
		return (ft_free(NULL, config, NULL), ft_error(MUTEX_ERR, NULL, 0));
	if (!init_fork(config))
		return (0);
	new_philos = (t_philo *)malloc(sizeof(t_philo)
			* config->philo_count);
	if (!new_philos)
		return (ft_destroy_mutex_array(config->mutex_fork, config->fork_count), \
			ft_free(NULL, config, config->mutex_fork), \
			ft_error(MEMORY_ERR, NULL, 0));
	i = -1;
	while (++i < config->philo_count)
		init_philo(new_philos + i, i, config, config->mutex_fork);
	*philos = new_philos;
	return (1);
}
