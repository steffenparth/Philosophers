/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:59:07 by sparth            #+#    #+#             */
/*   Updated: 2024/03/13 18:20:13 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

typedef struct s_input {
	int				nbr_of_philos;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				meals2eat;
	long			init_time;
	long			time_alive;
	bool			is_dead;
	pid_t			*pids;
	sem_t			*semaphore;
	sem_t			*sem_limit;
	sem_t			*sem_print;
	sem_t			*sem_finish;
	pthread_t		*thread;
}					t_input;

void	time2(int time, t_input *data, int philo_id);
long	get_time(void);
void	free_return(t_input *data, int errnum, int fork_dest, int philo_id);
void	print_func(char *status, t_input *data, int philo_id);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
