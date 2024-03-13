/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:43:07 by sparth            #+#    #+#             */
/*   Updated: 2024/03/11 18:45:57 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	error_message(int errnum, t_input *data)
{
	if (errnum == 1)
		printf("mutex initialization failed\n");
	if (errnum == 2)
		printf("memory allocation failed\n");
	if (errnum == 3)
		printf("pthread_create failed\n");
	if (errnum == 4)
		printf("pthread_join failed\n");
	if (errnum == 5)
		printf("Max Philos = 200\n");
	if (errnum == 6)
		printf("input: nbr_of_philos time2live(ms) time2eat(ms) "
			"time2sleep(ms) meals2eat(optional)\n");
	if (errnum == 7)
		printf("pthread_mutex_destroy failed\n");
	if (errnum == 8)
	{
		pthread_mutex_lock(&data->death_lock);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->death_lock);
		printf("Thread Mutex failed!\n");
	}
	return (0);
}

int	free_return(t_input *data, int errnum, int fork_dest, int mutex_dest)
{
	if (data->thread)
		free(data->thread);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (mutex_dest > 0)
		pthread_mutex_destroy(&data->death_lock);
	if (mutex_dest > 1)
		pthread_mutex_destroy(&data->food);
	while (fork_dest--)
		pthread_mutex_destroy(&data->forks[fork_dest]);
	if (data)
		free(data);
	error_message(errnum, data);
	return (0);
}
