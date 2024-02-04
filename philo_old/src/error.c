#include "philo.h"

int	ft_error(int error, char *str)
{
	if (error)
		ft_putstr_fd("Error:\n", 2);
	else
		ft_putstr_fd("Error\n", 2);
	if (error == MEMORY_ERR)
		ft_putstr_fd("DAMN, no memory left on device", 2);
	ft_putstr_fd("\n", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}
