/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:24:32 by iomayr            #+#    #+#             */
/*   Updated: 2022/05/31 13:24:01 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	philos_activities(t_philo *philos)
{
	display_message("is thinking", philos->id, philos->data);
	pthread_mutex_lock(&philos->fork);
	display_message("has taken the first fork", philos->id, philos->data);
	pthread_mutex_lock(philos->next_fork);
	display_message("has taken the second fork", philos->id, philos->data);
	philos->should_die = ft_current_time() + philos->data->time_die;
	display_message("is eating", philos->id, philos->data);
	usleep(philos->data->time_eat * 1000);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_unlock(philos->next_fork);
	display_message("is sleeping", philos->id, philos->data);
	usleep(philos->data->time_sleep * 1000);
}

void	*ft_philosophers(void *philo)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)philo;
	philos->leave = 0;
	philos->should_die = philos->data->s_time + philos->data->time_die;
	while (i < philos->data->must_eat || !(philos->data->must_eat))
	{
		philos_activities(philos);
		i++;
		usleep(100);
	}
	philos->leave = 1;
	return (NULL);
}

void	ft_fill_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (i == data->nb_philo - 1)
			philo[i].next_fork = &philo[0].fork;
		else
			philo[i].next_fork = &philo[i + 1].fork;
		i++;
	}
}

t_philo	*ft_create_philosophers(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (NULL);
	while (++i < data->nb_philo)
		pthread_mutex_init(&philo[i].fork, NULL);
	ft_fill_philo(data, philo);
	data->s_time = ft_current_time();
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_philosophers, &philo[i]))
			return (free(philo), NULL);
		usleep(10);
	}
	i = -1;
	while (++i < data -> nb_philo)
		pthread_detach(philo[i].thread);
	return (philo);
}
