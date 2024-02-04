#include "philo.h"

void	take_fork(char side_fork, t_philo *philo)
{
	int		*taken;
	t_fork	*fork;

	if (!is_philo_dead(philo))
	{
		taken = &(philo->is_rf_taken);
		fork = philo->r_fork;
		if (side_fork == 'l')
		{
			taken = &(philo->is_lf_taken);
			fork = philo->l_fork;
		}
		pthread_mutex_lock(&(fork->mutex));
		if (!(*taken) && !fork->in_use)
		{
			*taken = 1;
			fork->in_use = 1;
			pthread_mutex_unlock(&(fork->mutex));
			ft_print_state("has taken a fork", philo);
		}
		else
			pthread_mutex_unlock(&(fork->mutex));
	}
}

void	release_fork(char side_fork, t_philo *philo)
{
	int		*taken;
	t_fork	*fork;

	taken = &(philo->is_rf_taken);
	fork = philo->r_fork;
	if (side_fork == 'l')
	{
		taken = &(philo->is_lf_taken);
		fork = philo->l_fork;
	}
	pthread_mutex_lock(&(fork->mutex));
	*taken = 0;
	fork->in_use = 0;
	pthread_mutex_unlock(&(fork->mutex));
}
