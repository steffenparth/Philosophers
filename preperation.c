/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preperation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:38:23 by sparth            #+#    #+#             */
/*   Updated: 2024/03/10 02:33:27 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	preperation(int argc, char *argv[], t_input *data)
{
	int	i;

	i = 0;
	if (!init_struct(argc, argv, data))
		return (0);
	if (argc < 5 || argc > 6)
		return (free_return(data, false, 0, 3));
	if (!check_input(argc, argv))
		return (free_return(data, false, 0, 3));
	data->thread = malloc(sizeof(pthread_t) * (data->philo_nbr + 1));
	if (!data->thread)
		return (free_return(data, false, 0, 3));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (free_return(data, false, 0, 3));
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (free_return(data, false, i, 3));
		i++;
	}
	if (!create_philos(data))
		return (free_return(data, 0, data->philo_nbr, 3));
	return (1);
}

bool	init_struct(int argc, char *argv[], t_input *data)
{
	data->thread = NULL;
	data->forks = NULL;
	data->philo = NULL;
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (free_return(data, false, 0, 0));
	if (pthread_mutex_init(&data->check1, NULL) != 0)
		return (free_return(data, false, 0, 1));
	if (pthread_mutex_init(&data->check2, NULL) != 0)
		return (free_return(data, false, 0, 2));
	data->philo_nbr = ft_atoi(argv[1]);
	data->time2die = ft_atoi(argv[2]);
	data->time2eat = ft_atoi(argv[3]);
	data->time2sleep = ft_atoi(argv[4]);
	data->is_dead = false;
	data->finished = false;
	if (argc == 6)
		data->meals2eat = ft_atoi(argv[5]);
	else
		data->meals2eat = -1;
	return (true);
}

bool	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) ||
				(argv[i][j] == '+' && ft_isdigit(argv[i][j + 1])))
				j++ ;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

int	create_philos(t_input *data)
{
	int				i;
	struct timeval	tp;

	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (0);
	gettimeofday(&tp, NULL);
	while (i < data->philo_nbr)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_nbr;
		data->philo[i].meals2eat = data->meals2eat;
		data->philo[i].init_time = tp.tv_usec / 1000 + tp.tv_sec * 1000;
		data->philo[i].death_count = data->philo[i].init_time;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}
