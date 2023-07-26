/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:27:52 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/26 09:31:52 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct t_fork
{
	pthread_mutex_t fork;
	int				i;
	int 		forkid;
}				t_fork;

typedef struct to_do
{

	int				numb_philo;
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
	int 			currentflag;
	int 			*death_event;
	int				meal_plan;
	int				*meal_eaten;
    pthread_t		t;
	t_fork			*left;
	t_fork			*right;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *death_lock;
	pthread_mutex_t *eat_lock;
	struct timeval 	m;
	struct timezone y;
}				to_do;


int starter(to_do *dolist , char *argc[], int death);
int	checker(char *ptr[]);
void inint_fork_placement( to_do *dolist, t_fork *fork, int i);
int forkmanup(t_fork *forkes, int len, int flag);
void	setdolist(to_do *dolist, char *argc[], int i);
void philo_utils_inint(to_do dolist[], t_fork *forkes, char* argc[],int length);
void mutex_events(to_do *philos, int flag);
int deathchecker (to_do *philo);
void evenlife (to_do *philos);
void oddlife (to_do *philos);
void life( to_do *philos);
void *routine( void *philo_invoid);
int eating(to_do *philos);
void activity(  to_do * doa, long int *count,long int *limit  );
void statusprint(to_do *dolist);



#endif
