/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:11 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 11:20:32 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include<semaphore.h>
# include<sys/time.h>

typedef struct s_philo
{
	int				id;
	int				count;
	int				l_fork;
	int				r_fork;
	long long		last;
	pthread_t		ph_t;
	pthread_t		death;
	pthread_mutex_t	m_death;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_count;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				stop;
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				num_eat;
	long long		start_t;	
	t_philo			*philo;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	print_m;
}	t_data;
//parsing.c
int			ft_atoi(const char *str);
int			fill(t_data *data, int ac, char **av);
int			is_digit(char **av);
int			philo_malloc(t_data *data);
//simulation.c
int			start_threads(t_data *data);
void		*routin(void *data);
void		*death(void *data);
int			check_stop(t_data *da, int i);
int			check_count(t_data *da);
//simulation2.c
long long	t_time(void);
int			mutex_init(t_data *data);
int			ft_join(t_data *data);
void		ft_usleep(long long time, int time_to_sleep);
void		update_last(t_data *da);
//routin.c
void		print_ph(t_philo *ph, t_data *da, char *s);
void		thinking(t_philo *ph, t_data *da);
void		taking_forks(t_philo *ph, t_data *da);
void		eating(t_philo *ph, t_data *da);
void		sleeping(t_philo *ph, t_data *da);
//philo.c
void		finish_simulation(t_data *data);
void		fill_philo(t_data *data);
#endif