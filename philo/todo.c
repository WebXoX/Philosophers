/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:48:42 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/31 12:28:44 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

void	statusprint(t_philo *dolist)
{
	pthread_mutex_lock(dolist->print_mutex);
	if (deathchecker(dolist) == 1)
	{
		printf("%ld ms: ", dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000
			- dolist->time_birth);
		if (dolist->currentflag == 1)
		{
			printf("%d has taken a fork\n", dolist->numb_philo);
			printf("%ld ms: %d has taken a fork\n", (dolist->m.tv_sec * 1000
					+ dolist->m.tv_usec / 1000 - dolist->time_birth),
				dolist->numb_philo);
			printf("%ld ms: %d is eating\n", dolist->m.tv_sec * 1000
				+ dolist->m.tv_usec / 1000 - dolist->time_birth,
				dolist->numb_philo);
		}
		else if (dolist->currentflag == 2)
			printf("%d is sleeping\n", dolist->numb_philo);
		else if (dolist->currentflag == 3)
			printf("%d is thinking\n", dolist->numb_philo);
	}
	pthread_mutex_unlock(dolist->print_mutex);
	if (dolist->currentflag < 3)
		dolist->currentflag++;
	else if (dolist->currentflag == 3)
		dolist->currentflag = 1;
}

void	death_print(t_philo *doa)
{
	pthread_mutex_lock(doa->print_mutex);
	printf("%ld ms: %d is died\n", doa->m.tv_sec * 1000 + doa->m.tv_usec / 1000
		- doa->time_birth, doa->numb_philo);
	pthread_mutex_unlock(doa->print_mutex);
}

int	eating(t_philo *philos, int flag)
{
	if (flag == 1)
		mutex_events(philos);
	else
		mutex_events2(philos);
	return (0);
}

void	activity(t_philo *doa, long int *count, long int *limit)
{
	gettimeofday(&(doa->m), &(doa->y));
	doa->time_round = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000;
	*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000
		- (doa->time_round);
	statusprint(doa);
	while (*count < *limit && deathchecker(doa) == 1)
	{
		gettimeofday(&(doa->m), &(doa->y));
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000
			- (doa->time_round);
		doa->counttime_die = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000
			- (doa->time_round_death);
		pthread_mutex_lock(doa->death_lock);
		if (*(doa->death_event) == 0 && doa->counttime_die == doa->time_die)
		{
			*(doa->death_event) = 1;
			pthread_mutex_unlock(doa->death_lock);
			doa->currentflag = 4;
			death_print(doa);
			break ;
		}
		else
			pthread_mutex_unlock(doa->death_lock);
	}
}

void	ft_usleep(int limit, t_philo *philo, long int count, long int loop_time)
{
	long int	current_time;

	gettimeofday(&(philo->m), &(philo->y));
	current_time = (philo->m).tv_sec * 1000 + (philo->m).tv_usec / 1000;
	loop_time = (philo->m).tv_sec * 1000 + (philo->m).tv_usec / 1000;
	while (count <= limit && deathchecker(philo) == 1)
	{
		gettimeofday(&(philo->m), &(philo->y));
		loop_time = (philo->m).tv_sec * 1000 + (philo->m).tv_usec / 1000;
		count = loop_time - current_time;
		philo->counttime_die = loop_time - (philo->time_round_death);
		pthread_mutex_lock(philo->death_lock);
		if (*(philo->death_event) == 0
			&& philo->counttime_die == philo->time_die)
		{
			*(philo->death_event) = 1;
			pthread_mutex_unlock(philo->death_lock);
			philo->currentflag = 4;
			death_print(philo);
			break ;
		}
		else
			pthread_mutex_unlock(philo->death_lock);
	}
}
