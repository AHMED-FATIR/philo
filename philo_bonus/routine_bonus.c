/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:57:31 by afatir            #+#    #+#             */
/*   Updated: 2023/05/11 18:44:19 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_ph(t_philo *ph, char *s)
{
	check_stop(ph, 0);
	sem_wait(ph->data->print_s);
	printf("%lld\t%d\t%s\n", t_time() - ph->data->start_t, ph->id, s);
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
	sem_wait(ph->data->last_s);
	ph->last = t_time();
	sem_post(ph->data->last_s);
	ft_usleep(t_time(), ph->data->t_eat);
	if (ph->data->num_eat)
		check_count(ph, 1);
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
