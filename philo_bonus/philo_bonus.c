/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:58:25 by sparth            #+#    #+#             */
/*   Updated: 2024/03/13 23:41:07 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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


void	free_return(t_input *data, int errnum, int fork_dest, int philo_id)
{
	int	i;
	// pid_t	last_pid_to_kill;

	i = 0;
	errnum = 0;
	fork_dest = 0;
	if (data)
		free(data);
	sem_close(data->semaphore);
	sem_close(data->sem_print);
	sem_unlink("sem");
	sem_unlink("limit");
	if (philo_id)
	{
		printf("check\n");
		sem_post(data->sem_limit);
		sem_close(data->sem_limit);
		sem_unlink("print");
	}
	sem_close(data->sem_limit);
	sem_unlink("print");
	exit (1);
}

void	init_struct(int argc, char *argv[], t_input *data)
{
	
	data->nbr_of_philos = ft_atoi(argv[1]);
	if (data->nbr_of_philos > 200)
		free_return(data, 5, 0, 2);
	data->time2die = ft_atoi(argv[2]);
	data->time2eat = ft_atoi(argv[3]);
	data->time2sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals2eat = ft_atoi(argv[5]);
	else
		data->meals2eat = -1;
	data->semaphore = sem_open("sem", O_CREAT, 0644, data->nbr_of_philos);
	if (data->semaphore == SEM_FAILED)
		free_return(data, 0, 0, 0);
	data->sem_limit = sem_open("limit", O_CREAT, 0644, data->nbr_of_philos / 2);
	if (data->sem_limit == SEM_FAILED)
		free_return(data, 0, 0, 0);
	data->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		free_return(data, 0, 0, 0);
	data->sem_finish = sem_open("finish", O_CREAT, 0644, 0);
	if (data->sem_finish == SEM_FAILED)
		free_return(data, 0, 0, 0);
	// sem_unlink("sem");
	// sem_unlink("limit");
	// sem_unlink("print");
	// sem_unlink("finish");
	data->is_dead = false;
	data->init_time = get_time();
	data->time_alive = data->init_time;
}

void	preperation(int argc, char *argv[], t_input *data)
{
	init_struct(argc, argv, data);
	if (argc < 5 || argc > 6)
		free_return(data, 6, 0, 2);
	if (!check_input(argc, argv))
		free_return(data, false, 0, 2);

}

void	eating(t_input *data, int philo_id)
{
	if (sem_wait(data->sem_limit) == -1)
		free_return(data, 0, 0, 0);
	if (sem_wait(data->semaphore) == -1)
		free_return(data, 0, 0, 0);
	print_func("has taken a fork", data, philo_id);
	if (sem_wait(data->semaphore) == -1)
		free_return(data, 0, 0, 0);
	print_func("has taken a fork", data, philo_id);
	print_func("is eating", data, philo_id);
	data->time_alive = get_time();
	time2(data->time2eat, data, philo_id);
	if (sem_post(data->semaphore) == -1)
		free_return(data, 0, 0, 0);
	if (sem_post(data->semaphore) == -1)
		free_return(data, 0, 0, 0);
	if (sem_post(data->sem_limit) == -1)
		free_return(data, 0, 0, 0);
}

void	sleeping(t_input *data, int philo_id)
{
	print_func("is sleeping", data, philo_id);
	time2(data->time2sleep, data, philo_id);
}
void	thinking(t_input *data, int philo_id)
{
	int	temp;

	print_func("is thinking", data, philo_id);
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
	while(data->meals2eat--)
	{
		eating(data, philo_id);
		sleeping(data, philo_id);
		thinking(data, philo_id);
	}
	sem_post(data->sem_finish);
	exit (0);
}

void	create_processes(t_input *data)
{
	pid_t	pid;
	int		i;

	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->nbr_of_philos);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pid = fork();
		if (pid == -1)
			free_return(data, 0, 0, 0);
		else if (pid == 0)
			routine(data, i + 1);
		else
			data->pids[i] = pid;
		i++;
	}
	i = 0;
	sem_wait(data->sem_finish);
	while (i < data->nbr_of_philos)
	{
		// printf("i: %d\n", i);
		kill(data->pids[i], SIGTERM);
		i++;
	}
	// sem_post(data->sem_print);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_input *data;
	int		i;

	i = 0;
	data = (t_input *)malloc(sizeof(t_input));
	if (!data)
		return (1);
	sem_close(data->semaphore);
	sem_close(data->sem_limit);
	sem_close(data->sem_print);
	sem_close(data->sem_finish);
	sem_unlink("sem");
	sem_unlink("limit");
	sem_unlink("print");
	sem_unlink("finish");
	preperation(argc, argv, data);
	create_processes(data);
	sem_close(data->semaphore);
	sem_close(data->sem_limit);
	sem_close(data->sem_print);
	sem_close(data->sem_finish);
	sem_unlink("sem");
	sem_unlink("limit");
	sem_unlink("print");
	sem_unlink("finish");
	return (0);
}