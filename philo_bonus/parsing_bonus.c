/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:50:42 by afatir            #+#    #+#             */
/*   Updated: 2023/05/07 16:53:36 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int							i;
	int							s;
	unsigned long long			res;

	i = 0;
	s = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		if (res > 9223372036854775807 && s == 1)
			return (-1);
		else if (res > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return (res * s);
}

int	is_digit(char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= 48 && av[i][j] <= 59))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	fill(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->num_eat = ft_atoi(av[5]);
		if (!data->num_eat)
			return (0);
	}
	if (!data->num_philo || !data->t_die ||!data->t_eat || !data->t_sleep)
		return (0);
	return (1);
}

int	philo_malloc(t_data *data)
{
	data->philo = (t_philo *)malloc(data->num_philo * sizeof(t_philo));
	if (!data->philo)
		return (0);
	return (1);
}
