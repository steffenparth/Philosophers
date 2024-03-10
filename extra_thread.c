/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:45:38 by sparth            #+#    #+#             */
/*   Updated: 2024/03/10 02:28:17 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_food_handeling(t_input *data, int i)
{
	if (get_time() - data->philo[i].death_count == data->time2die)
	{
		pthread_mutex_lock(&data->death_lock);
		data->is_dead = 1;
		printf("%ld %d died\n", get_time()
			- data->philo[i].init_time, data->philo[i].ID);
		pthread_mutex_unlock(&data->death_lock);
		return (0);
	}
	pthread_mutex_lock(&data->check1);
	if (data->philo[i].death_reset)
	{
		data->philo[i].death_count = get_time();
		data->philo[i].death_reset = 0;
	}
	pthread_mutex_unlock(&data->check1);
	pthread_mutex_lock(&data->check2);
	if (data->finished == true)
	{
		pthread_mutex_unlock(&data->check2);
		return (0);
	}
	pthread_mutex_unlock(&data->check2);
	return (1);
}

void	*observation(void *arg)
{
	t_input	*data;
	int		i;

	data = (t_input *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			if (!death_food_handeling(data, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
