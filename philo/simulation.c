/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:00:58 by afatir            #+#    #+#             */
/*   Updated: 2023/05/13 17:46:36 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_data *data)
{
	int		i;

	i = 0;
	if (!mutex_init(data))
		return (0);
	while (i < data->num_philo)
	{
		update_last(&data->philo[i], data);
		if (pthread_create (&data->philo[i].ph_t, \
			NULL, routin, &data->philo[i]) != 0)
			return (0);
		if (pthread_create (&data->philo[i].death, \
			NULL, death, &data->philo[i]) != 0)
			return (0);
		i++;
	}
	if (!ft_join(data))
		return (0);
	return (1);
}

void	*routin(void *data)
{
	t_philo	*ph;
	t_data	*da;

	ph = (t_philo *) data;
	da = ph->data;
	if (ph->id == 0)
		da->start_t = t_time();
	if (ph->id % 2 != 0 && da->num_philo != 1)
		usleep (200);
	while (1)
	{
		if (check_stop(da, 0))
			break ;
		taking_forks(ph, da);
		if (da->num_philo == 1)
			break ;
		eating(ph, da);
		if (check_count(da))
			break ;
		sleeping(ph, da);
		thinking(ph, da);
		ft_usleep(t_time(), 2);
	}
	return (NULL);
}

void	*death(void *data)
{
	t_philo	*ph;
	t_data	*da;

	ph = (t_philo *) data;
	da = ph->data;
	while (1)
	{
		if (check_last(ph, da))
		{
			if (check_stop(da, 0) || check_count(da))
				break ;
			check_stop(da, 1);
			pthread_mutex_lock(&da->print_m);
			printf("%lld\t%d\t%s\n", (t_time() - ph->data->start_t), \
			ph->id + 1, "died");
			pthread_mutex_unlock(&da->print_m);
			return (NULL);
		}
		ft_usleep(t_time(), 2);
	}
	return (NULL);
}

int	check_stop(t_data *da, int i)
{
	pthread_mutex_lock(&da->philo->m_stop);
	if (i == 1)
		da->stop++;
	else if (i == 0)
	{
		if (da->stop)
		{
			pthread_mutex_unlock(&da->philo->m_stop);
			return (1);
		}
	}
	pthread_mutex_unlock(&da->philo->m_stop);
	return (0);
}

int	check_count(t_data *da)
{	
	if (da->num_eat)
	{
		pthread_mutex_lock(&da->philo->m_count);
		if (da->philo->count == da->num_eat)
		{
			pthread_mutex_unlock(&da->philo->m_count);
			return (1);
		}
		pthread_mutex_unlock(&da->philo->m_count);
	}
	return (0);
}
