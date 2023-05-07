/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:24:42 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 18:15:01 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_philo(t_data *data)
{
	int		i;

	i = 0;
	data->start_t = t_time();
	while (i < data->num_philo)
	{
		data->philo[i].count = 0;
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].last = data->start_t;
		i++;
	}	
}

int	main(int ac, char **av)
{
	t_data	data;
	pid_t	*f_pid;

	// printf("%d\n", getpid());
	if ((ac != 5 && ac != 6) || !is_digit(av) || \
		!fill(&data, ac, av) || !philo_malloc(&data))
		return (printf("THE ARGUMENT IS WRONG\n"), 1);
	fill_philo(&data);
	f_pid = start_simulation(&data);
	if (!f_pid)
		return (free(data.philo), free(f_pid), 0);
	sem_close(data.fork_s);
	sem_close(data.print_s);
	// sem_close(&data.philo->count_s);
	// sem_close(&data.philo->last_s);
	finish_simulation(&data, f_pid, 0);
	free(f_pid);
	free(data.philo);
	// while (1)
	// {
	// 	/* code */
	// }
	return (0);
}
