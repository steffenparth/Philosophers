/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:07:30 by sparth            #+#    #+#             */
/*   Updated: 2024/03/17 04:06:14 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_processes(t_input *data)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		pid = fork();
		if (pid == -1)
			cleanup(data);
		else if (pid == 0)
			routine(data, i + 1);
		else
			data->pids[i] = pid;
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philos)
		waitpid(data->pids[i++], NULL, 0);
}

void	preperation(int argc, char *argv[], t_input *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("input: nbr_of_philos time2live(ms) time2eat(ms) "
			"time2sleep(ms) meals2eat(optional)\n");
		free(data);
		exit (1);
	}
	if (!check_input(argc, argv))
	{
		printf("only positive numbers allowed\n");
		free(data);
		exit (1);
	}
	init_struct(argc, argv, data);
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

void	init_struct(int argc, char *argv[], t_input *data)
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	if (data->nbr_of_philos > 200 || data->nbr_of_philos < 2)
	{
		free(data);
		printf("nbr of philos min. 2 & max. 200\n");
		exit (1);
	}
	data->time2die = ft_atoi(argv[2]);
	data->time2eat = ft_atoi(argv[3]);
	data->time2sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals2eat = ft_atoi(argv[5]);
	else
		data->meals2eat = -1;
	data->forks = sem_creating(data, "forks", data->nbr_of_philos);
	data->sem_limit = sem_creating(data, "limit", data->nbr_of_philos / 2);
	data->sem_print = sem_creating(data, "print", 1);
	data->sem_finish = sem_creating(data, "finish", 0);
	data->sem_if_finished = sem_creating(data, "if_finished", 1);
	data->finished = false;
	data->init_time = get_time();
	data->last_meal = data->init_time;
}

sem_t	*sem_creating(t_input *data, char *sem_name, int sem_nbr)
{
	sem_t	*sem;

	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, sem_nbr);
	if (sem == SEM_FAILED)
	{
		printf("sem_open failed\n");
		printf("%s\n", sem_name);
		cleanup(data);
		exit (1);
	}
	return (sem);
}
