/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:08:51 by afatir            #+#    #+#             */
/*   Updated: 2023/05/12 17:44:28 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_count(t_philo *ph, int i)
{
	if (i == 0)
	{
		if (ph->data->num_eat && ph->data->num_eat <= ph->count)
			exit(0);
	}
	else
		ph->count++;
}

long long	t_time(void)
{
	struct timeval	tm;
	long long		t;

	t = 0;
	if (gettimeofday(&tm, NULL) == -1)
		return (printf("gettimeofday failed\n"), 0);
	t = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (t);
}

void	ft_usleep(long long time, int time_to_sleep, t_philo *ph)
{
	while ((int)(t_time() - time) < time_to_sleep)
	{
		if ((t_time() - ph->last) >= ph->data->t_die)
		{
			sem_wait(ph->data->print_s);
			printf("%lld\t%d\t%s\n", t_time() - ph->data->start_t, ph->id, "died");
			exit(1);
		}
		usleep(100);
	}
}
