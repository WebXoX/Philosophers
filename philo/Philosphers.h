/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:27:52 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/31 12:44:49 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_fork
{
	pthread_mutex_t	fork;
	int				i;
	int				forkid;
}					t_fork;

typedef struct to_do
{
	int				numb_philo;
	int				totoal_numb_philo;
	long int		time_birth;
	long int		time_round;
	long int		time_round_death;
	long int		time_current;
	long int		time_eat;
	long int		time_sleep;
	long int		time_thinking;
	long int		time_die;
	long int		counttime_eat;
	long int		counttime_sleep;
	long int		counttime_thinking;
	long int		counttime_die;
	int				currentflag;
	int				*death_event;
	int				meal_plan;
	int				individual_meal_plan;
	int				individual_meal_eaten;
	int				*meal_eaten;
	pthread_t		t;
	t_fork			*left;
	t_fork			*right;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*eat_lock;
	struct timeval	m;
	struct timezone	y;
}					t_philo;

int					starter(t_philo *dolist, char *argc[], int death);
int					checker(char *ptr[]);
void				inint_fork_placement(t_philo *dolist, t_fork *fork, int i);
int					forkmanup(t_fork *forkes, int len, int flag);
void				setdolist(t_philo *dolist, char *argc[], int i);
void				philo_utils_inint(t_philo *dolist, t_fork *forkes,
						char *argc[], int length);
void				mutex_events(t_philo *philos);
void				mutex_events2(t_philo *philos);
int					deathchecker(t_philo *philo);
void				evenlife(t_philo *philos);
void				oddlife(t_philo *philos);
void				life(t_philo *philos);
void				*routine(void *philo_invoid);
int					eating(t_philo *philos, int flag);
void				activity(t_philo *doa, long int *count, long int *limit);
void				statusprint(t_philo *dolist);
void				ft_usleep(int limit, t_philo *philo, long int count,
						long int loop_time);
int					ft_atoi(const char *nptr, int *status, int sign);

#endif
