/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:00:58 by afatir            #+#    #+#             */
/*   Updated: 2023/05/13 07:25:16 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

pid_t	*start_simulation(t_data *data)
{
	int		i;
	pid_t	pid;
	pid_t	*f_pid;

	i = 0;
	if (!init_semaphore(data))
		return (0);
	f_pid = (pid_t *)malloc(data->num_philo * sizeof(int));
	if (!f_pid)
		return (0);
	while (i < data->num_philo)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		if (pid == 0)
		{
			if (!routine(&data->philo[i]))
				return (0);
		}
		else
			f_pid[i] = pid;
		i++;
	}
	return (f_pid);
}

int	routine(t_philo *ph)
{
	while (1)
	{
		taking_forks(ph);
		eating(ph);
		sleeping(ph);
		thinking(ph);
		if (ph->data->num_eat)
			check_count(ph, 0);
	}
	return (1);
}

int	init_semaphore(t_data *da)
{
	sem_unlink("fork_s");
	sem_unlink("print_s");
	da->fork_s = sem_open("fork_s", O_CREAT, 0777, da->num_philo);
	da->print_s = sem_open("print_s", O_CREAT, 0777, 1);
	if ((da->fork_s == SEM_FAILED) || (da->print_s == SEM_FAILED))
		return (0);
	return (1);
}

void	finish_simulation(t_data *data, int *f_pid, int id)
{
	int		i;
	int		stat;

	i = 0;
	if (id == data->num_philo)
		return ;
	waitpid(-1, &stat, 0);
	if (WIFEXITED(stat) && !WEXITSTATUS(stat))
		return (finish_simulation(data, f_pid, id + 1));
	else
	{	
		while (i < data->num_philo)
		{
			kill(f_pid[i], SIGKILL);
			i++;
		}
	}
	return ;
}
