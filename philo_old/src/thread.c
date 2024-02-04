#include "philo.h"

int	init_threads(t_philo **philos, t_config *config)
{
	int	i;

	config->start_time = get_timestamp();
	i = -1;
	while (++i < config->philo_count)
		if (pthread_create(&(*philos)[i].thread, NULL,
			philo_life, &((*philos[i]))))
			return (0);
	if (pthread_create(&(config->dead_thread), NULL,
			check_philos_state, philos))
		return (0);
	return (1);
}

int	wait_threads(t_philo **philos, t_config *config)
{
	int	i;
	int	status;

	i = -1;
	status = 1;
	while (++i < config->philo_count)
		if (pthread_join((*philos)[i].thread, NULL))
			status = 0;
	return (status);
}

int	kill_threads(t_philo *philo)
{
	pthread_mutex_lock(&(philo->config->dead_mutex));
	philo->config->dead_count = 1;
	pthread_mutex_unlock(&(philo->config->dead_mutex));
	return (EXIT_FAILURE);
}
