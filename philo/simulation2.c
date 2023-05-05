/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:24:02 by afatir            #+#    #+#             */
/*   Updated: 2023/05/05 16:33:50 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	t_time(void)
{
	struct timeval	tm;
	long long		t;

	t = 0;
	if (gettimeofday(&tm, NULL) == -1)
		ft_print_error("gettimeofday failed\n");
	t = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (t);
}

int	mutex_init(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->fork_m[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->philo->m_death, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->philo->m_stop, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->philo->m_count, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->print_m, NULL) != 0)
		return (0);
	return (1);
}

void	finish_simulation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&(data->fork_m[i]));
		i++;
	}
	pthread_mutex_destroy(&data->philo->m_death);
	pthread_mutex_destroy(&data->philo->m_stop);
	pthread_mutex_destroy(&data->philo->m_count);
	pthread_mutex_destroy(&data->print_m);
	free (data->philo);
	free (data->fork_m);
}

int	ft_join(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philo[i].ph_t, NULL) != 0)
			return (0);
		if (pthread_join(data->philo[i].death, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_usleep(long long time, int time_to_sleep)
{
	while ((int)(t_time() - time) < time_to_sleep)
		usleep(100);
}
