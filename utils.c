/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:17:18 by sparth            #+#    #+#             */
/*   Updated: 2024/03/10 02:25:06 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	free_return(t_input *data, bool r_value, int fork_dest, int mutex_dest)
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
		pthread_mutex_destroy(&data->check1);
	if (mutex_dest > 2)
		pthread_mutex_destroy(&data->check2);
	while (fork_dest--)
		pthread_mutex_destroy(&data->forks[fork_dest]);
	if (data)
		free(data);
	return (r_value);
}

void	mutex_terminate(t_input *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			printf("pthread_mutex_destroy failed");
		i++;
	}
	if (pthread_mutex_destroy(&data->death_lock))
		printf("pthread_mutex_destroy failed");
	if (pthread_mutex_destroy(&data->check1))
		printf("pthread_mutex_destroy failed");
	if (pthread_mutex_destroy(&data->check2))
		printf("pthread_mutex_destroy failed");
}

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_usec / 1000 + tp.tv_sec * 1000);
}
