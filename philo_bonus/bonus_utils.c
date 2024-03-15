/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:29:15 by sparth            #+#    #+#             */
/*   Updated: 2024/03/16 00:39:02 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec / 1000 + tp.tv_sec * 1000);
}

void	time2(int time, t_input *data, int philo_id)
{
	long	temp;
	long	current_time;

	temp = get_time();
	while (1)
	{
		current_time = get_time();
		sem_wait(data->sem_print);
		if (data->finished == true)
		{
			sem_post(data->sem_print);
			// sem_post(data->sem_finish);
			usleep (50);
			clean_process(data);
			exit (1);
		}
		if (current_time - data->last_meal >= data->time2die)
		{
			
			printf("%ld %d \033[31mdied\033[0m\n", current_time - data->init_time, philo_id);
			sem_post(data->sem_print);
			sem_post(data->sem_finish);
			usleep (50);
			clean_process(data);
			exit (1);
		}
		if ((current_time - temp) >= time)
		{
			sem_post(data->sem_print);
			break ;
		}
		sem_post(data->sem_print);
		usleep(50);
	}
}

void	print_func(char *status, t_input *data, int philo_id)
{
	long	current_time;

	sem_wait(data->sem_print);
	current_time = get_time();
	if (data->finished == true)
	{
		sem_post(data->sem_print);
		// sem_post(data->sem_finish);
		clean_process(data);
		exit (1);
	}
	if (current_time - data->last_meal >= data->time2die)
	{
		printf("%ld %d \033[31mdied\033[0m\n", current_time - data->init_time, philo_id);
		sem_post(data->sem_print);
		sem_post(data->sem_finish);
		// pthread_join(data->thread, NULL);
		clean_process(data);
		exit (1);
	}
	else
		printf("%ld %d %s\n", current_time - data->init_time, philo_id, status);
	sem_post(data->sem_print);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	count;
	size_t	minuscheck;

	i = 0;
	count = 0;
	minuscheck = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minuscheck *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		count *= 10;
		count += str[i] - 48;
		i++;
	}
	return (count * minuscheck);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
