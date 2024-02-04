#include "philo.h"

int	ft_print_state(char *str, t_philo *philo)
{
	int		printed;
	long	current_time;

	printed = 0;
	current_time = get_timestamp() - philo->config->start_time;
	pthread_mutex_lock(&(philo->config->main_mutex));
	if (!is_philo_dead(philo))
		printed += printf("%09ld %d %s\n", current_time, philo->pos, str);
	pthread_mutex_unlock(&(philo->config->main_mutex));
	return (printed);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < time_in_ms)
		usleep(100);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
