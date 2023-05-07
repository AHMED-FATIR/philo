/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:11 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 18:16:58 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include<semaphore.h>
# include<sys/time.h>

typedef struct s_philo
{
	int				id;
	int				count;
	long long		last;
	pthread_t		ph_t;
	struct s_data	*data;
	sem_t			*count_s;
	sem_t			*last_s;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	long long		start_t;	
	t_philo			*philo;
	sem_t			*fork_s;
	sem_t			*print_s;
}	t_data;
//parsing.c
int			ft_atoi(const char *str);
int			fill(t_data *data, int ac, char **av);
int			is_digit(char **av);
int			philo_malloc(t_data *data);
//simulation.c
long long	t_time(void);
int			*start_simulation(t_data *data);
int			ch_process(t_philo *ph);
void		ft_exit(t_data *da, int i);
void		*routine(void *philo);
void		finish_simulation(t_data *data, int *f_pid, int id);
int			init_semaphore(t_data *da);
int			creat_threads(t_philo *ph);
//routin.c
void		print_ph(t_philo *ph, char *s);
void		thinking(t_philo *ph);
void		taking_forks(t_philo *ph);
void		eating(t_philo *ph);
void		sleeping(t_philo *ph);
//philo.c
void		ft_usleep(long long time, int time_to_sleep);
void		fill_philo(t_data *data);
#endif