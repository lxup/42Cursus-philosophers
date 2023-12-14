/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:21 by lquehec           #+#    #+#             */
/*   Updated: 2023/12/14 20:45:41 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEBUG 1

# ifdef DEBUG
#  include <stdio.h>
# endif
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define LONG_MIN -9223372036854775808
# define LONG_MAX 9223372036854775807

enum	e_errors
{
	MEMORY_ERR			= -1,
};

typedef struct s_philo
{
	int			id;
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_eat;
	int			*nb_eat_philo;
	int			*last_eat;
	sem_t		*semaphore;
	pthread_t	*threads;
}	t_philo;

#endif
