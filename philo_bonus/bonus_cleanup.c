/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:57:26 by sparth            #+#    #+#             */
/*   Updated: 2024/03/15 01:33:22 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_closing(sem_t *semaphore, char *sem_name)
{
	if (sem_close(semaphore) != 0)
	{
		printf("sem_close failed!\n");
		exit (1);
	}
	if (sem_unlink(sem_name) != 0)
	{
		printf("sem_unlink failed\n");
		exit (1);
	}
}

void	cleanup(t_input *data)
{
	if (data->forks != SEM_FAILED)
		sem_closing(data->forks, "forks");
	if (data->sem_limit != SEM_FAILED)
		sem_closing(data->sem_limit, "limit");
	if (data->sem_print != SEM_FAILED)
		sem_closing(data->sem_print, "print");
	if (data->sem_finish != SEM_FAILED)
		sem_closing(data->sem_finish, "finish");
	if (data->pids)
		free(data->pids);
	if (data)
		free(data);
}

void	exiting(t_input *data, int errnum)
{
	cleanup(data);
	printf("check\n");
	if (errnum == 1)
		printf("malloc failed\n");
	if (errnum == 2)
		printf("\n");
	if (errnum == 3)
		printf("\n");
	if (errnum == 4)
		printf("\n");
	if (errnum == 5)
		printf("\n");
	if (errnum == 6)
		printf("\n");
	exit (1);
}

void	ctrl_c_clean(void)
{
	sem_unlink("forks");
	sem_unlink("limit");
	sem_unlink("print");
	sem_unlink("finish");
}
