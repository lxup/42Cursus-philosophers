#include "philo.h"

void	init_philo(t_philo *philo, t_fork **forks, t_config *config, int pos)
{
	philo->config = config;
	philo->pos = pos;
	philo->time_last_eat = 0;
	philo->eat_count = 0;
	philo->r_fork = &((*forks)[pos]);
	philo->is_rf_taken = 0;
	if (pos == config->philo_count - 1)
		philo->l_fork = &((*forks)[0]);
	else
		philo->l_fork = &((*forks)[pos + 1]);
	philo->is_lf_taken = 0;
	philo->l_fork->in_use = 0;
	pthread_mutex_init(&(philo->last_eat_mutex), NULL);
	pthread_mutex_init(&(philo->l_fork->mutex), NULL);
}

int	init_philosophers(t_philo **philos, t_fork **forks, t_config *config)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * config->philo_count);
	if (!(*philos))
		return (ft_error(MEMORY_ERR, NULL), 0);
	*forks = (t_fork *)malloc(sizeof(t_fork) * config->philo_count);
	if (!(*forks))
		return (free(*philos), ft_error(MEMORY_ERR, NULL), 0);
	i = -1;
	while (++i < config->philo_count)
		init_philo(&(*philos)[i], forks, config, i);
	return (1);
}

int	init_config(t_config *config, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_error(ARGS_ERR, "Usage: ./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat](optional)");
		return (0);
	}
	config->philo_count = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		config->eat_count = ft_atoi(av[5]);
	else
		config->eat_count = -1;
	config->dead_count = 0;
	if (config->philo_count <= 0 || config->time_to_die < 0
		|| config->time_to_eat < 0 || config->time_to_sleep < 0
		|| (ac == 6 && config->eat_count < 0))
		return (0);
	pthread_mutex_init(&(config->main_mutex), NULL);
	pthread_mutex_init(&(config->dead_mutex), NULL);
	return (1);
}
