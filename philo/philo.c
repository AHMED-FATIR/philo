/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:24:42 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 11:26:20 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	fill_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].count = 0;
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].last = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->num_philo;
		i++;
	}	
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac != 5 && ac != 6) || !is_digit(av) || \
		!fill(&data, ac, av) || !philo_malloc(&data))
		return (printf("THE ARGUMENT IS WRONG\n"), 1);
	fill_philo(&data);
	if (!start_threads(&data))
		return(printf("THE PROGRAM FAILED\n"), 1);
	finish_simulation(&data);
	return (0);
}
