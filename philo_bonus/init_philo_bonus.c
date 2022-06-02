/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:24:32 by iomayr            #+#    #+#             */
/*   Updated: 2022/05/31 12:41:54 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	philo_activities(t_data *data)
{
	display_message("is thinking", data->id + 1, data);
	sem_wait(data->forks);
	display_message("has taken the first fork", data->id + 1, data);
	sem_wait(data->forks);
	display_message("has taken the second fork", data->id + 1, data);
	data->should_die = ft_current_time() + data->time_die;
	display_message("is eating", data->id + 1, data);
	usleep(data->time_eat * 1000);
	data->ate++;
	sem_post(data->forks);
	sem_post(data->forks);
	display_message("is sleeping", data->id + 1, data);
	usleep(data->time_sleep * 1000);
}

void	*ft_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->must_eat || !(data->must_eat))
	{
		philo_activities(data);
		i++;
		usleep(100);
	}
	return (NULL);
}

void	*ft_start_philosophers(t_data *data)
{
	int	i;

	i = -1;
	data->s_time = ft_current_time();
	while (++i < data->nb_philo)
	{
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] < 0)
			return (0);
		if (data->pid_philo[i] == 0)
		{
			data->id = i;
			data->ate = 0;
			data->should_die = ft_current_time() + data->time_die;
			pthread_create(&data->philo_id, NULL, &ft_check_health, data);
			pthread_detach(data->philo_id);
			ft_philosophers(data);
		}
	}
	return (NULL);
}
