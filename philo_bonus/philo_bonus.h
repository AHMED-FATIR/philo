/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:11 by afatir            #+#    #+#             */
/*   Updated: 2023/05/12 17:41:39 by afatir           ###   ########.fr       */
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
	struct s_data	*data;
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
void		fill_philo(t_data *data);
int			ft_atoi(const char *str);
int			fill(t_data *data, int ac, char **av);
int			is_digit(char **av);
int			philo_malloc(t_data *data);
//simulation.c
pid_t		*start_simulation(t_data *data);
int			routine(t_philo *ph);
int			init_semaphore(t_data *da);
void		finish_simulation(t_data *data, int *f_pid, int id);
//simulation2.c
void		check_count(t_philo *ph, int i);
long long	t_time(void);
void		ft_usleep(long long time, int time_to_sleep, t_philo *ph);
//routin.c
void		print_ph(t_philo *ph, char *s);
void		thinking(t_philo *ph);
void		taking_forks(t_philo *ph);
void		eating(t_philo *ph);
void		sleeping(t_philo *ph);
#endif