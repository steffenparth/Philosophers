/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:59:07 by sparth            #+#    #+#             */
/*   Updated: 2024/03/15 01:32:20 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h> 

typedef struct s_input
{
	int				nbr_of_philos;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				meals2eat;
	long			init_time;
	long			last_meal;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*sem_limit;
	sem_t			*sem_print;
	sem_t			*sem_finish;
	pthread_t		*thread;
}					t_input;

void	time2(int time, t_input *data, int philo_id);
long	get_time(void);
void	print_func(char *status, t_input *data, int philo_id);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	cleanup(t_input *data);
void	sem_closing(sem_t *semaphore, char *sem_name);
void	ctrl_c_clean(void);
void	exiting(t_input *data, int errnum);
bool	check_input(int argc, char *argv[]);
void	init_struct(int argc, char *argv[], t_input *data);
void	preperation(int argc, char *argv[], t_input *data);
sem_t	*sem_creating(t_input *data, char *sem_name, int sem_nbr);
void	create_processes(t_input *data);
