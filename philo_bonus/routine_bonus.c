/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:57:31 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 18:20:32 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_ph(t_philo *ph, char *s)
{
	sem_wait(ph->data->print_s);
	printf("%lld\11", t_time() - ph->data->start_t);
	printf("%d\11", ph->id);
	printf("%s\11\n", s);
	sem_post(ph->data->print_s);
}

void	thinking(t_philo *ph)
{
	print_ph(ph, "is thinking");
}

void	taking_forks(t_philo *ph)
{
	sem_wait(ph->data->fork_s);
	print_ph(ph, "has taken a fork");
	sem_wait(ph->data->fork_s);
	print_ph(ph, "has taken a fork");
}

void	eating(t_philo *ph)
{
	print_ph(ph, "is eating");
// sem_wait(ph->last_s);
	ph->last = t_time();
// sem_post(ph->last_s);
	ft_usleep(t_time(), ph->data->t_eat);
	if (ph->data->num_eat)
	{
// sem_wait(ph->count_s);
		ph->count++;
// sem_post(ph->count_s);
	}
	sem_post(ph->data->fork_s);
	sem_post(ph->data->fork_s);
}

void	sleeping(t_philo *ph)
{
	long long	st;

	st = t_time();
	print_ph(ph, "is sleeping");
	ft_usleep(t_time(), ph->data->t_sleep);
}
