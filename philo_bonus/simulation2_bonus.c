/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:08:51 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 18:17:32 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_data *da, int i)
{
	free(da->philo);
	exit(i);
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

void	ft_usleep(long long time, int time_to_sleep)
{
	while ((int)(t_time() - time) < time_to_sleep)
		usleep(100);
}

int	creat_threads(t_philo *ph)
{
	pthread_t	prc;

	if (pthread_create (&prc, NULL, routine, ph) != 0)
		return (0);
	if (pthread_detach(prc) != 0)
		return (0);
	return (1);
}
