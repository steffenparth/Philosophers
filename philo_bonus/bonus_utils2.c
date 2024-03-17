/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:14:39 by sparth            #+#    #+#             */
/*   Updated: 2024/03/17 04:13:51 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_exit(t_input *data, int flag, int philo_id)
{
	int		i;
	long	current_time;

	i = 0;
	current_time = get_time();
	if (flag == 1)
	{
		sem_post(data->sem_if_finished);
		pthread_join(data->thread, NULL);
		clean_process(data);
		exit (1);
	}
	if (flag == 2)
	{
		while (i++ < data->nbr_of_philos)
			sem_post(data->sem_finish);
		printf("%ld %d \033[31mdied\033[0m\n", current_time
			- data->init_time, philo_id);
		sem_post(data->sem_print);
		pthread_join(data->thread, NULL);
		clean_process(data);
		exit (1);
	}
}

void	*set_end(void *arg)
{
	t_input	*data;

	data = (t_input *)arg;
	sem_wait(data->sem_finish);
	sem_wait(data->sem_if_finished);
	data->finished = true;
	sem_post(data->sem_if_finished);
	return (NULL);
}

void	pre_routine(t_input *data, int philo_id)
{
	if (philo_id % 2 == 0)
		time2(data->time2eat, data, philo_id);
	if (philo_id % 2 != 0 && data->nbr_of_philos == philo_id)
		time2(data->time2eat * 2, data, philo_id);
}
