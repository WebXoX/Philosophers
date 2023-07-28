/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:48:42 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/28 13:01:31 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"



void statusprint(to_do *dolist)
{
	pthread_mutex_lock(dolist->print_mutex);
	// pthread_mutex_lock(dolist->death_lock);
	// printf("meal :%d philo : %d\n ",dolist->individual_meal_eaten, dolist->numb_philo);
	// if (dolist->individual_meal_eaten == dolist->individual_meal_plan )
	// {
	// 	pthread_mutex_unlock(dolist->print_mutex);
	// 	return ;
	// }	
		
	if( deathchecker(dolist) == 1)
	{
		// pthread_mutex_unlock(dolist->death_lock);
			printf("%ld ms: ", dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth);
		if (dolist->currentflag == 1)
		{
			printf("%d has taken a fork\n", dolist->numb_philo);
			printf("%ld ms: %d has taken a fork\n",(dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth), dolist->numb_philo);
			printf("%ld ms: %d is eating\n",dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth,  dolist->numb_philo);
		}
		else if (dolist->currentflag == 2)
			printf("%d is sleeping\n", dolist->numb_philo);
		else if (dolist->currentflag == 3)
			printf("%d is thinking\n", dolist->numb_philo);
	}
	// else
	// 	pthread_mutex_lock(dolist->death_lock);
	pthread_mutex_unlock(dolist->print_mutex);

}

void eating(to_do *philos, int flag)
{
	if (flag == 1)
			mutex_events(philos,1);
	else 
			mutex_events2(philos,1);
		return(0);
}

void activity(  to_do * doa, long int *count,long int *limit  )
{
		gettimeofday(&(doa->m), &(doa->y));
		doa->time_round = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000;
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_round);
		statusprint(doa);
		while ( *count < *limit && deathchecker(doa == 0))
		{
			gettimeofday(&(doa->m), &(doa->y));
			*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round);
			doa->counttime_die = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round_death);
				pthread_mutex_lock(doa->death_lock);
			if ( *(doa->death_event) == 0 && doa->counttime_die == doa->time_die )
			{
					*(doa->death_event) = 1;
				pthread_mutex_unlock(doa->death_lock);
					doa->currentflag = 4;
				pthread_mutex_lock(doa->print_mutex);
					printf("%ld ms: %d is died\n", doa->m.tv_sec * 1000 + doa->m.tv_usec / 1000 - doa->time_birth, doa->numb_philo);
				pthread_mutex_unlock(doa->print_mutex);
				break;
			}
			else
				pthread_mutex_unlock(doa->death_lock);
		}
	if(doa->currentflag < 3)
		doa->currentflag++;
	else if( doa->currentflag == 3)
		doa->currentflag = 1;
}


void ft_usleep( int limit, to_do *philo,long int count, long int loop_time)
{
	long int current_time;
	
	gettimeofday(&(philo->m), &(philo->y));
	current_time = (philo->m).tv_sec * 1000 + (philo->m).tv_usec / 1000;
	loop_time = (philo->m).tv_sec * 1000 + (philo->m).tv_usec / 1000;
	while( count < limit && deathchecker(philo)==0)
	{
		gettimeofday(&(philo->m), &(philo->y));
		loop_time = (philo->m).tv_sec * 1000 + (philo->m).tv_usec/1000 ;
		count = loop_time - current_time;
		philo->counttime_die = (philo->m).tv_sec * 1000 + (philo->m).tv_usec/1000  - (philo->time_round_death);
		pthread_mutex_lock(philo->death_lock);
		if ( *(philo->death_event) == 0 && philo->counttime_die == philo->time_die )
		{
				*(philo->death_event) = 1;
			pthread_mutex_unlock(philo->death_lock);
				philo->currentflag = 4;
			pthread_mutex_lock(philo->print_mutex);
				printf("%ld ms: %d is died\n", philo->m.tv_sec * 1000 + philo->m.tv_usec / 1000 - philo->time_birth, philo->numb_philo);
			pthread_mutex_unlock(philo->print_mutex);
			break;
		}
		else
			pthread_mutex_unlock(philo->death_lock);
	}
}
