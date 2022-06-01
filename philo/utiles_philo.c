/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 11:43:51 by ibra              #+#    #+#             */
/*   Updated: 2022/05/31 12:57:47 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (++j < ft_strlen(av[i]))
		{
			if ((av[i][j] < 48 || av[i][j] > 57) && av[i][j] != '+')
				return (1);
		}
	}
	return (0);
}

int	check_input(int ac, char **av, t_data *data)
{
	if (ac != 6 && ac != 5)
		return (printf("wrong arguments\n"), 1);
	if (check_digit(ac, av))
		return (printf("check the content of your param\n"), 1);
	data->must_eat = 1;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 1)
			return (0);
	}
	if (ac == 5)
		data->must_eat = 0;
	if (data->nb_philo < 1 || data->time_die < 60
		|| data->time_eat < 60 || data->time_sleep < 60)
		return (1);
	return (0);
}

void	display_message(char *s, int id, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("[%ld] %d %s\n", ft_current_time() - data->s_time, id, s);
	fflush(stdout);
	pthread_mutex_unlock(&data->print);
}
