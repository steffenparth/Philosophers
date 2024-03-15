/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:58:25 by sparth            #+#    #+#             */
/*   Updated: 2024/03/15 01:33:43 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_input *data, int philo_id)
{
	if (sem_wait(data->sem_limit) == -1)
		cleanup(data);
	if (sem_wait(data->forks) == -1)
		cleanup(data);
	print_func("has taken a fork", data, philo_id);
	if (sem_wait(data->forks) == -1)
		cleanup(data);
	print_func("has taken a fork", data, philo_id);
	print_func("\x1b[31mis eating\x1b[0m", data, philo_id);
	data->last_meal = get_time();
	time2(data->time2eat, data, philo_id);
	if (sem_post(data->forks) == -1)
		cleanup(data);
	if (sem_post(data->forks) == -1)
		cleanup(data);
	if (sem_post(data->sem_limit) == -1)
		cleanup(data);
}

void	sleeping(t_input *data, int philo_id)
{
	print_func("\x1b[32mis sleeping\x1b[0m", data, philo_id);
	time2(data->time2sleep, data, philo_id);
}

void	thinking(t_input *data, int philo_id)
{
	int	temp;

	print_func("\x1b[33mis thinking\x1b[0m", data, philo_id);
	if (data->nbr_of_philos % 2 != 0)
	{
		temp = data->time2eat * 2 - data->time2sleep;
		if (temp > 0)
			time2(temp, data, philo_id);
	}
	else
	{
		temp = data->time2eat - data->time2sleep;
		if (temp > 0)
			time2(temp, data, philo_id);
	}
}

void	routine(t_input	*data, int philo_id)
{
	while (data->meals2eat--)
	{
		eating(data, philo_id);
		sleeping(data, philo_id);
		thinking(data, philo_id);
	}
	sem_post(data->sem_finish);
	exit (0);
}

int	main(int argc, char *argv[])
{
	t_input	*data;

	data = (t_input *)malloc(sizeof(t_input));
	if (!data)
	{
		printf("malloc failed\n");
		return (1);
	}
	ctrl_c_clean();
	preperation(argc, argv, data);
	create_processes(data);
	cleanup(data);
	return (0);
}
