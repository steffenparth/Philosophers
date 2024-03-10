/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:41:04 by sparth            #+#    #+#             */
/*   Updated: 2024/03/10 02:32:24 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_input	t_input;

typedef struct s_philo
{
	long	timestamp;
	int		id;
	int		left_fork;
	int		right_fork;
	int		meals2eat;
	bool	death_reset;
	long	init_time;
	long	death_count;
	t_input	*data;
}			t_philo;

typedef struct s_input {
	int				philo_nbr;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				meals2eat;
	bool			is_dead;
	bool			finished;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	check1;
	pthread_mutex_t	check2;
}					t_input;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
bool	preperation(int argc, char *argv[], t_input *data);
bool	init_struct(int argc, char *argv[], t_input *data);
bool	check_input(int argc, char *argv[]);
int		create_philos(t_input *data);
int		free_return(t_input *data, bool r_value, int fork_dest, int mutex_dest);
void	mutex_terminate(t_input *data);
void	time2(int time);
void	thinking(t_philo *phil);
bool	eating(t_philo *phil);
void	pre_routine(t_philo *phil);
long	get_time(void);
bool	print_func(char *status, t_philo *data);
bool	death_food_handeling(t_input *data, int i);
void	*observation(void *arg);
bool	sleeping(t_philo *phil);
int		main(int argc, char *argv[]);
bool	threading(t_input *data);
void	*routine(void *arg);
bool	print_func(char *status, t_philo *data);
