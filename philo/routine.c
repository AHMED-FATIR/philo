/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:57:31 by afatir            #+#    #+#             */
/*   Updated: 2023/05/05 17:03:23 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_ph(t_philo *ph, t_data *da, char *s)
{
	if (check_stop(da, 0))
		return ;
	pthread_mutex_lock(&da->print_m);
	printf("%lld\t%d\t%s\n", (t_time() - ph->data->start_t), ph->id + 1, s);
	pthread_mutex_unlock(&da->print_m);
}

void	thinking(t_philo *ph, t_data *da)
{
	print_ph(ph, da, "is thinking");
}

void	taking_forks(t_philo *ph, t_data *da)
{
	if (da->num_philo == 1)
	{
		pthread_mutex_lock(&da->fork_m[ph->r_fork]);
		print_ph(ph, da, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&da->fork_m[ph->r_fork]);
		print_ph(ph, da, "has taken a fork");
		pthread_mutex_lock(&da->fork_m[ph->l_fork]);
		print_ph(ph, da, "has taken a fork");
	}
}

void	eating(t_philo *ph, t_data *da)
{
	if (da->num_philo == 1)
	{
		ft_usleep(t_time(), da->t_die);
		pthread_mutex_unlock(&da->fork_m[ph->r_fork]);
		return ;
	}
	else
	{
		print_ph(ph, da, "is eating");
		pthread_mutex_lock(&da->philo->m_death);
		ph->last = t_time();
		pthread_mutex_unlock(&da->philo->m_death);
		ft_usleep(t_time(), da->t_eat);
		if (da->num_eat)
		{
			pthread_mutex_lock(&da->philo->m_count);
			ph->count++;
			pthread_mutex_unlock(&da->philo->m_count);
		}
		pthread_mutex_unlock(&da->fork_m[ph->r_fork]);
		pthread_mutex_unlock(&da->fork_m[ph->l_fork]);
	}
}

void	sleeping(t_philo *ph, t_data *da)
{
	long long	st;

	st = t_time();
	print_ph(ph, da, "is sleeping");
	ft_usleep(t_time(), da->t_sleep);
}
