/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:24:42 by afatir            #+#    #+#             */
/*   Updated: 2023/05/05 16:26:44 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	v(void)
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_data	data;
	// atexit(v);
	if ((ac != 5 && ac != 6) || !is_digit(av) || \
		!fill(&data, ac, av) || !philo_malloc(&data))
		ft_print_error("wrong argument\n");
	fill_philo(&data);
	if (!start_threads(&data))
		ft_print_error("the program failed\n");
	finish_simulation(&data);
	return (0);
}
