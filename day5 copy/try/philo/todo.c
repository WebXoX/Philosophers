#include "Philosphers.h"



void statusprint(to_do *dolist)
{
	pthread_mutex_lock(dolist->print_mutex);
	// pthread_mutex_lock(dolist->death_lock);
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

int eating(to_do *philos)
{
	// if (deathchecker(philos) == 0)
	// 		return 1;
		// pthread_mutex_lock(&philos->right->fork);
		// pthread_mutex_lock(&philos->left->fork);
	// if(philos->right->i == 1 && philos->left->i == 1)
	// 	{
	// 		pthread_mutex_unlock(&philos->right->fork);
	// 		pthread_mutex_unlock(&philos->left->fork);
	// 		gettimeofday(&(philos->m), &(philos->y));
	// 		philos->counttime_die = 0;
	// 		philos->time_round_death = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000;

			// if (deathchecker(philos) == 0)
			// 	return 0;
			mutex_events(philos,1);
			// activity(philos, &philos->counttime_eat, &philos->time_eat);
		// 	mutex_events(philos,2);
		// 	return (1);
		// }
		// else
		// {
		// 	pthread_mutex_unlock(&philos->left->fork);
		// 	pthread_mutex_unlock(&philos->right->fork);
		// }
		return(0);
}

int eating2(to_do *philos)
{
	// if (deathchecker(philos) == 0)
	// 		return 1;
		// pthread_mutex_lock(&philos->right->fork);
		// pthread_mutex_lock(&philos->left->fork);
	// if(philos->right->i == 1 && philos->left->i == 1)
	// 	{
	// 		pthread_mutex_unlock(&philos->right->fork);
	// 		pthread_mutex_unlock(&philos->left->fork);
	// 		gettimeofday(&(philos->m), &(philos->y));
	// 		philos->counttime_die = 0;
	// 		philos->time_round_death = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000;

			// if (deathchecker(philos) == 0)
			// 	return 0;
			mutex_events2(philos,1);
			// activity(philos, &philos->counttime_eat, &philos->time_eat);
		// 	mutex_events(philos,2);
		// 	return (1);
		// }
		// else
		// {
		// 	pthread_mutex_unlock(&philos->left->fork);
		// 	pthread_mutex_unlock(&philos->right->fork);
		// }
		return(0);
}

void activity(  to_do * doa, long int *count,long int *limit  )
{
	 	if (deathchecker(doa)==0)
				return ;
		gettimeofday(&(doa->m), &(doa->y));
		doa->time_round = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000;
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_round);
		statusprint(doa);
		while( *count < *limit)
		{
			gettimeofday(&(doa->m), &(doa->y));
			*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round);
			doa->counttime_die = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round_death);
			if (deathchecker(doa) == 0)
				return ;
			// usleep(1);
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
	// if (*(doa->death_event) == 0)
	// 			return ;
	if(doa->currentflag < 3)
		doa->currentflag++;
	else if( doa->currentflag == 3)
		doa->currentflag = 1;

	// usleep(5);
}


void ft_usleep( int limit, to_do *philo )
{
	struct timeval	m;
	struct timezone	y;
	long int current_time;
	long int loop_time;
	long int count;

	count = 0;
	// philo->numb_philo = philo->numb_philo;
	gettimeofday(&m, &y);
		current_time = (m).tv_sec * 1000 + (m).tv_usec / 1000;
		loop_time = (m).tv_sec * 1000 + (m).tv_usec / 1000;
	 	if (deathchecker(philo)==0)
				return ;
		while( count < limit)
		{
			// if (deathchecker(philo) == 0)
			// 	return ;
			gettimeofday(&(m), &(y));
			loop_time = (m).tv_sec * 1000 + (m).tv_usec/1000 ;
			count = loop_time - current_time;
			philo->counttime_die = (philo->m).tv_sec * 1000 + (philo->m).tv_usec/1000  - (philo->time_round_death);
			// printf("%ld ms\n", loop_time current_time);

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
