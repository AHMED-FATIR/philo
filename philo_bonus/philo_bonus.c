/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:24:42 by afatir            #+#    #+#             */
/*   Updated: 2023/05/12 17:56:58 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	pid_t	*f_pid;

	if ((ac != 5 && ac != 6) || !is_digit(av) || \
		!fill(&data, ac, av) || !philo_malloc(&data))
		return (printf("THE ARGUMENT IS WRONG\n"), 1);
	fill_philo(&data);
	f_pid = start_simulation(&data);
	if (!f_pid)
		return (free(data.philo), free(f_pid), 0);
	finish_simulation(&data, f_pid, 0);
	sem_close(data.fork_s);
	sem_close(data.print_s);
	sem_unlink("fork_s");
	sem_unlink("print_s");
	free(f_pid);
	free(data.philo);
	return (0);
}
