/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:57:23 by sparth            #+#    #+#             */
/*   Updated: 2024/03/11 18:49:57 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_func(char *status, t_philo *phil)
{
	if (pthread_mutex_lock(&phil->data->death_lock) != 0)
		return (error_message(8, phil->data));
	if (!phil->data->is_dead)
	{
		phil->timestamp = get_time() - phil->init_time;
		printf("%ld %d %s\n", phil->timestamp, phil->id, status);
		if (pthread_mutex_unlock(&phil->data->death_lock) != 0)
			return (error_message(8, phil->data));
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&phil->data->death_lock);
		return (false);
	}
}

bool	check_if_finished(t_philo *phil)
{
	if (pthread_mutex_lock(&phil->data->food) != 0)
		return (error_message(8, phil->data));
	if (phil->data->finished == true)
	{
		if (pthread_mutex_unlock(&phil->data->food) != 0)
			return (error_message(8, phil->data));
		return (0);
	}
	if (pthread_mutex_unlock(&phil->data->food) != 0)
		return (error_message(8, phil->data));
	return (1);
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
		if (!check_if_finished(phil))
			return (NULL);
		if (!thinking(phil))
			return (NULL);
	}
	if (!set_finished(phil))
		return (NULL);
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
			return (free_return(data, 3, data->philo_nbr, 2));
		i++;
	}
	if (pthread_create(&data->thread[i], NULL, &observation, data) != 0)
		return (free_return(data, 3, data->philo_nbr, 2));
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return (free_return(data, 4, data->philo_nbr, 2));
		i++;
	}
	if (pthread_join(data->thread[i], NULL) != 0)
		return (free_return(data, 4, data->philo_nbr, 2));
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
