/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:45:38 by sparth            #+#    #+#             */
/*   Updated: 2024/03/17 03:38:11 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_food_handeling(t_input *data, int i)
{
	if (pthread_mutex_lock(&data->death_lock) != 0)
		return (error_message(8, data));
	if (get_time() - data->philo[i].death_count >= data->time2die)
	{
		data->is_dead = 1;
		printf("%ld %d died\n", get_time()
			- data->philo[i].init_time, data->philo[i].id);
		pthread_mutex_unlock(&data->death_lock);
		return (0);
	}
	if (pthread_mutex_unlock(&data->death_lock) != 0)
		return (error_message(8, data));
	if (pthread_mutex_lock(&data->food) != 0)
		return (error_message(8, data));
	if (data->finished == true)
	{
		pthread_mutex_unlock(&data->food);
		return (0);
	}
	if (pthread_mutex_unlock(&data->food) != 0)
		return (error_message(8, data));
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
		usleep (50);
	}
	return (NULL);
}

void	pre_routine(t_philo *phil)
{
	if (phil->id % 2 == 0)
		time2(phil->data->time2eat * 0.7);
	if (phil->id % 2 != 0 && phil->data->philo_nbr == phil->id
		&& phil->data->philo_nbr % 2 != 0 && phil->id != 1)
		time2((phil->data->time2eat * 2) * 0.7);
}

bool	set_finished(t_philo *phil)
{
	if (pthread_mutex_lock(&phil->data->food) != 0)
		return (error_message(8, phil->data));
	phil->data->finished = true;
	if (pthread_mutex_unlock(&phil->data->food) != 0)
		return (error_message(8, phil->data));
	return (1);
}
