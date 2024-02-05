#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&(philo->config->dead_mutex));
	is_dead = philo->config->dead_count;
	pthread_mutex_unlock(&(philo->config->dead_mutex));
	return (is_dead);
}

int	check_philo_death(t_philo *philo, long current_time)
{
	int		is_dead;
	long	time_last_eat;

	is_dead = 0;
	pthread_mutex_lock(&(philo->last_eat_mutex));
	time_last_eat = current_time - philo->time_last_eat;
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	if (time_last_eat > philo->config->t_die)
	{
		pthread_mutex_lock(&(philo->config->main_mutex));
		pthread_mutex_lock(&(philo->config->dead_mutex));
		philo->config->dead_count = 1;
		pthread_mutex_unlock(&(philo->config->dead_mutex));
		printf("%09ld %d died\n", current_time, philo->pos);
		pthread_mutex_unlock(&(philo->config->main_mutex));
		is_dead = 1;
	}
	return (is_dead);
}

void	*check_philos_state(void *data)
{
	t_philo		**philos;
	t_config	*config;
	long		current_time;
	int			i;

	philos = (t_philo **)data;
	config = philos[0]->config;
	while (1)
	{
		i = -1;
		current_time = get_timestamp() - config->start_time;
		while (++i < config->philo_count)
			if (check_philo_death(&(*philos)[i], current_time))
				return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}

void	sleep_after_eating(t_philo *philo)
{
	release_fork('r', philo);
	release_fork('l', philo);
	ft_print_state("is sleeping", philo);
	ft_usleep(philo->config->t_sleep);
}

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->pos % 2 != 0)
		ft_usleep(philo->config->t_eat);
	while (!is_philo_dead(philo))
	{
		if (philo->eat_count >= philo->config->eat_count
			&& philo->config->eat_count > 0)
			break ;
		take_fork('l', philo);
		if (philo->is_lf_taken)
			take_fork('r', philo);
		if (philo->is_lf_taken && philo->is_rf_taken)
		{
			ft_print_state("is eating", philo);
			ft_usleep(philo->config->t_eat);
			philo->eat_count++;
			pthread_mutex_lock(&(philo->last_eat_mutex));
			philo->time_last_eat = get_timestamp() - philo->config->start_time;
			pthread_mutex_unlock(&(philo->last_eat_mutex));
			sleep_after_eating(philo);
		}
	}
	return (NULL);
}
