/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:48 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/11 19:57:53 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*thread_routine(void *data)
{
	pthread_t		tid;
	t_counter		*counter;
	unsigned int	i;

	tid = pthread_self();
	counter = (t_counter *)data;
	pthread_mutex_lock(&counter->counter_mutex);
	printf("%sTHREAD [%ld]: DEPART = %u.%s\n", YELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->counter_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&counter->counter_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->counter_mutex);
		i++;
	}
	pthread_mutex_lock(&counter->counter_mutex);
	printf("%sTHREAD [%ld]: FIN = %u.%s\n", BYELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->counter_mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_counter	counter;

	counter.count = 0;
	pthread_mutex_init(&counter.counter_mutex, NULL);
	printf("MAIN: Conter attendu = %s%s%s\n", GREEN, TIMES_TO_COUNT * 2, NC);
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("MAIN: THREAD [%ld] créé\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("MAIN: THREAD [%ld] créé\n", tid2);
	pthread_join(tid1, NULL);
	printf("MAIN: THREAD [%ld] join\n", tid1);
	pthread_join(tid2, NULL);
	printf("MAIN: THREAD [%ld] join\n", tid2);
	if (counter.count != (2 * TIMES_TO_COUNT))
		printf("%sMAIN: ERREUR: Counter = %u.%s\n", RED, counter.count, NC);
	else
		printf("%sMAIN: OK: Counter = %u.%s\n", GREEN, counter.count, NC);
	pthread_mutex_destroy(&counter.counter_mutex);
	return (0);
}
