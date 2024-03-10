/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:37:26 by sparth            #+#    #+#             */
/*   Updated: 2024/03/10 02:23:49 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time2(int time)
{
	long			temp;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	temp = tp.tv_usec / 1000 + tp.tv_sec * 1000;
	while (1)
	{
		gettimeofday(&tp, NULL);
		if (((tp.tv_usec / 1000 + tp.tv_sec * 1000) - temp) >= time)
			return ;
		usleep(50);
	}
	printf("error???\n");
	return ;
}

void	thinking(t_philo *phil)
{
	int	temp;

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
}

bool	eating(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	print_func("has taken a fork", phil);
	if (phil->data->philo_nbr == 1)
	{
		pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	print_func("has taken a fork", phil);
	if (!print_func("is eating", phil))
	{
		pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
		pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&phil->data->check1);
	phil->death_reset = 1;
	pthread_mutex_unlock(&phil->data->check1);
	time2(phil->data->time2eat);
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	return (1);
}

void	pre_routine(t_philo *phil)
{
	if (phil->ID % 2 == 0)
		time2(phil->data->time2eat * 0.7);
	if (phil->ID % 2 != 0 && phil->data->philo_nbr == phil->ID
		&& phil->data->philo_nbr % 2 != 0 && phil->ID != 1)
		time2((phil->data->time2eat * 2) * 0.7);
}

bool	sleeping(t_philo *phil)
{
	if (!print_func("is sleeping", phil))
		return (0);
	time2(phil->data->time2sleep);
	return (1);
}
