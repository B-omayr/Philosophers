/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:49:56 by iomayr            #+#    #+#             */
/*   Updated: 2022/05/31 12:46:02 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include <semaphore.h>
# include <unistd.h>

typedef struct s_data
{
	sem_t		*forks;
	sem_t		*print;
	sem_t		*death;
	int			id;
	int			leave;
	int			state;
	long		should_die;
	pthread_t	philo_id;
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;
	long		s_time;
	int			ate;
	int			status;
	pid_t		pid_philo[200];
}	t_data;
void	display_message(char *s, int id, t_data *data);
int		ft_initialize_sem(t_data *data);
int		check_input(int ac, char **av, t_data *data);
void	*ft_start_philosophers(t_data *data);
long	ft_current_time(void);
void	display_message(char *s, int id, t_data *data);
void	*ft_check_health(void *dataa);
int		ft_strcmp(char *str, char *ptr);

#endif