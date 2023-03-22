/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:25:46 by afatir            #+#    #+#             */
/*   Updated: 2023/03/21 10:45:24 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;
int beers = 2000000;

void* drink_lots(void *a);

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, drink_lots, NULL);
    pthread_create(&thread2, NULL, drink_lots, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("beers = %i\n", beers);
    return 0;
}

void* drink_lots(void *a)
{
	(void)a;
	int i;

	pthread_mutex_lock(&beers_lock);
	for (i = 0; i < 100000; i++)
		beers = beers - 1;
	pthread_mutex_unlock(&beers_lock);
	printf("beers = %i\n", beers);
	return NULL;
}
