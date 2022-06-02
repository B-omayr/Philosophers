/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:48:09 by iomayr            #+#    #+#             */
/*   Updated: 2022/05/31 16:15:14 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_initialize_sem(t_data *data)
{
	sem_unlink("message");
	data->print = sem_open("message", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (0);
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		return (0);
	return (1);
}

void	display_message(char *s, int id, t_data *data)
{
	sem_wait(data->print);
	printf("[%ld] %d %s\n", ft_current_time() - data->s_time, id, s);
	fflush(stdout);
	if (ft_strcmp(s, "died") != 0)
		sem_post(data->print);
}

void	clear(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		kill(data->pid_philo[i], SIGKILL);
	sem_close(data->print);
	sem_close(data->forks);
	sem_unlink("/print");
	sem_unlink("/forks");
}

void	*ft_check_health(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		if (data->must_eat)
		{
			if (data->ate == data->must_eat)
				exit (1);
		}
		if (ft_current_time() >= data->should_die + 1)
		{
			display_message("died", data->id + 1, data);
			usleep(1000);
			exit (0);
		}
		usleep (1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		state;
	int		i;

	i = 0;
	if (check_input(ac, av, &data))
		return (0);
	if (!ft_initialize_sem(&data))
		return (0);
	ft_start_philosophers(&data);
	while (waitpid(-1, &state, 0) != -1)
		if (state == 0)
			clear(&data);
	return (0);
}
