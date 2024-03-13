/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:29:15 by sparth            #+#    #+#             */
/*   Updated: 2024/03/13 21:27:55 by sparth           ###   ########.fr       */
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
		if (current_time - data->time_alive >= data->time2die)
		{
			sem_wait(data->sem_print);
			printf("%ld %d died1\n", current_time - data->init_time, philo_id);
			sem_post(data->sem_finish);
			return ;
		}
		if ((current_time - temp) >= time)
			break ;

		usleep(50);
	}
}

void	print_func(char *status, t_input *data, int philo_id)
{
	long current_time;
	
	sem_wait(data->sem_print);
	current_time = get_time();
	if (current_time - data->time_alive >= data->time2die)
	{
		printf("%ld %d died2\n", current_time - data->init_time, philo_id);
		sem_post(data->sem_finish);
		return ;
		// free_return(data, 0, 0, philo_id);
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