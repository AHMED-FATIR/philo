/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:00:58 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 18:19:30 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	*start_simulation(t_data *data)
{
	int		i;
	pid_t	pid;
	pid_t	*f_pid;

	i = 0;
	if (!init_semaphore(data))
		return (0);
	f_pid = (pid_t *)malloc(data->num_philo * sizeof(int));
	while (i < data->num_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!ch_process(&data->philo[i]))
				return (0);
		}
		else
			f_pid[i] = pid;
		i++;
	}
	return (f_pid);
}

int	ch_process(t_philo *ph)
{
	if (!creat_threads(ph))
		return (0);
	while (1)
	{
// sem_wait(ph->count_s);
		if (ph->data->num_eat && ph->data->num_eat == ph->count)
		{
// sem_post(ph->count_s);
			ft_exit(ph->data, 0);
		}
// sem_post(ph->count_s);
// sem_wait(ph->last_s);
		if ((t_time() - ph->last) > ph->data->t_die)
		{
			print_ph(ph, "died");
// sem_post(ph->last_s);
			ft_exit(ph->data, 1);
		}
// sem_post(ph->last_s);
		usleep(50);
	}
	return (1);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = philo;
	if (ph->id % 2 == 0 && ph->data->num_philo != 1)
		ft_usleep(t_time(), 2);
	while (1)
	{
		taking_forks(ph);
		eating(ph);
		sleeping(ph);
		thinking(ph);
		usleep(500);
	}
	return (NULL);
}

int	init_semaphore(t_data *da)
{
	sem_unlink("fork_s");
	sem_unlink("print_s");
	sem_unlink("count_s");
	sem_unlink("last_s");
	da->fork_s = sem_open("fork_s", O_CREAT, 0777, da->num_philo);
	da->print_s = sem_open("print_s", O_CREAT, 0777, 1);
	da->philo->count_s = sem_open("count_s", O_CREAT, 0777, 1);
	da->philo->last_s = sem_open("last_s", O_CREAT, 0777, 1);
	if ((da->fork_s == SEM_FAILED) || (da->print_s == SEM_FAILED) \
		|| (da->philo->count_s == SEM_FAILED) || \
		(da->philo->last_s == SEM_FAILED))
		return (0);
	return (1);
}

void	finish_simulation(t_data *data, int *f_pid, int id)
{
	int		i;
	int		stat;

	if (id == data->num_philo)
		return ;
	waitpid(-1, &stat, 0);
	if (WIFEXITED(stat))
	{
		if (WEXITSTATUS(stat))
		{
			i = -1;
			while (++i < data->num_philo)
				kill(f_pid[i], SIGKILL);
		}
		else
			return (finish_simulation(data, f_pid, id + 1));
	}
	else
	{
		i = -1;
		while (++i < data->num_philo)
			kill(f_pid[i], SIGKILL);
	}
	return ;
}
