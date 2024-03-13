/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:37:26 by sparth            #+#    #+#             */
/*   Updated: 2024/03/11 18:49:39 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thinking(t_philo *phil)
{
	int	temp;

	if (!print_func("is thinking", phil))
		return (0);
	if (phil->data->philo_nbr % 2 != 0)
	{
		temp = phil->data->time2eat * 2 - phil->data->time2sleep;
		if (temp > 0)
			time2(temp);
	}
	else
	{
		temp = phil->data->time2eat - phil->data->time2sleep;
		if (temp > 0)
			time2(temp);
	}
	return (1);
}

bool	fork_locking(t_philo *phil, int fork_1, int fork_2)
{
	if (pthread_mutex_lock(&phil->data->forks[fork_1]) != 0)
		return (error_message(8, phil->data));
	if (!print_func("has taken a fork", phil))
	{
		pthread_mutex_unlock(&phil->data->forks[fork_1]);
		return (0);
	}
	if (phil->data->philo_nbr == 1)
	{
		pthread_mutex_unlock(&phil->data->forks[fork_1]);
		return (0);
	}
	if (pthread_mutex_lock(&phil->data->forks[fork_2]) != 0)
	{
		pthread_mutex_unlock(&phil->data->forks[fork_1]);
		return (error_message(8, phil->data));
	}
	if (!print_func("has taken a fork", phil))
	{
		pthread_mutex_unlock(&phil->data->forks[fork_1]);
		pthread_mutex_unlock(&phil->data->forks[fork_2]);
		return (0);
	}
	return (1);
}

bool	time2live_reset(t_philo *phil)
{
	if (pthread_mutex_lock(&phil->data->death_lock) != 0)
		return (error_message(8, phil->data));
	phil->death_count = get_time();
	if (pthread_mutex_unlock(&phil->data->death_lock) != 0)
		return (error_message(8, phil->data));
	return (1);
}

bool	eating(t_philo *phil)
{
	if (phil->left_fork < phil->right_fork)
	{
		if (!fork_locking(phil, phil->left_fork, phil->right_fork))
			return (0);
	}
	else
	{
		if (!fork_locking(phil, phil->right_fork, phil->left_fork))
			return (0);
	}
	if (!print_func("is eating", phil))
	{
		pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
		pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
		return (0);
	}
	if (!time2live_reset(phil))
		return (0);
	time2(phil->data->time2eat);
	if (pthread_mutex_unlock(&phil->data->forks[phil->right_fork]) != 0)
		return (0);
	if (pthread_mutex_unlock(&phil->data->forks[phil->left_fork]) != 0)
		return (0);
	return (1);
}

bool	sleeping(t_philo *phil)
{
	if (!print_func("is sleeping", phil))
		return (0);
	time2(phil->data->time2sleep);
	return (1);
}
