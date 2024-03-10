/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:57:23 by sparth            #+#    #+#             */
/*   Updated: 2024/03/10 02:32:39 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_func(char *status, t_philo *data)
{
	pthread_mutex_lock(&data->data->death_lock);
	if (!data->data->is_dead)
	{
		data->timestamp = get_time() - data->init_time;
		printf("%ld %d %s\n", data->timestamp, data->id, status);
		pthread_mutex_unlock(&data->data->death_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&data->data->death_lock);
		return (false);
	}
}

void	*routine(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	pre_routine(phil);
	while (phil->meals2eat--)
	{
		if (!eating(phil))
			return (NULL);
		if (!sleeping(phil))
			return (NULL);
		pthread_mutex_lock(&phil->data->check2);
		if (phil->data->finished == true)
		{
			pthread_mutex_unlock(&phil->data->check2);
			return (NULL);
		}
		pthread_mutex_unlock(&phil->data->check2);
		if (!print_func("is thinking", phil))
			return (NULL);
		thinking(phil);
	}
	pthread_mutex_lock(&phil->data->check2);
	phil->data->finished = true;
	pthread_mutex_unlock(&phil->data->check2);
	return (NULL);
}

bool	threading(t_input *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->thread[i],
				NULL, &routine, &data->philo[i]) != 0)
			return (free_return(data, 0, data->philo_nbr, 3));
		i++;
	}
	if (pthread_create(&data->thread[i], NULL, &observation, data) != 0)
		return (free_return(data, 0, data->philo_nbr, 3));
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return (free_return(data, 0, data->philo_nbr, 3));
		i++;
	}
	if (pthread_join(data->thread[i], NULL) != 0)
		return (free_return(data, 0, data->philo_nbr, 3));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_input	*data;

	data = (t_input *)malloc(sizeof(t_input));
	if (!data)
		return (1);
	if (!preperation(argc, argv, data))
		return (1);
	if (!threading(data))
		return (1);
	mutex_terminate(data);
	return (free_return(data, false, 0, 0));
}
