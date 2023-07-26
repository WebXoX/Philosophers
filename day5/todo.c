#include "Philosphers.h"



void statusprint(to_do *dolist)
{
	pthread_mutex_lock(dolist->print_mutex);
	if( *(dolist->death_event) != 1)
	{	
			printf("%ld ms: ", dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth);
		if (dolist->currentflag == 1)
		{
			printf("%d has taken a fork\n", dolist->numb_philo);
			printf("%ld ms: %d has taken a fork\n",(dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth), dolist->numb_philo);
			printf("%ld ms: %d is eating\n",dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth,  dolist->numb_philo);
		}
		if (dolist->currentflag == 2)
			printf("%d is sleeping\n", dolist->numb_philo);
		if (dolist->currentflag == 3)
			printf("%d is thinking\n", dolist->numb_philo);
	}
	pthread_mutex_unlock(dolist->print_mutex);

}

int eating(to_do *philos)
{
	if((philos->meal_plan) != 0 && *philos->meal_eaten == philos->meal_plan)
		{
			philos->currentflag = 4;
			return 0;
		}
	if(philos->right->i == 1 && philos->left->i == 1)
		{
			gettimeofday(&(philos->m), &(philos->y));
			philos->counttime_die = 0;
			philos->time_round_death = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000;

			// if (deathchecker(philos) == 0)
			// 	return 0;
			mutex_events(philos,1);
				activity(philos, &philos->counttime_eat, &philos->time_eat);
			mutex_events(philos,2);
			return (1);
		}
		return(0);
}


void activity(  to_do * doa, long int *count,long int *limit  )
{
	gettimeofday(&(doa->m), &(doa->y));
		doa->time_round = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000;
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_round);
	 	// if (deathchecker(doa)==0)
		// 		return ;
		statusprint(doa);
		while( *count < *limit)
		{
			gettimeofday(&(doa->m), &(doa->y));
			*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round);
			doa->counttime_die = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round_death);
			// if (deathchecker(doa) == 0)
			// 	return ;
			usleep(1);
			pthread_mutex_lock(doa->death_lock);
			if ( deathchecker(doa) == 1 && *(doa->death_event) == 0 && doa->counttime_die == doa->time_die )
			{
					*(doa->death_event) = 1;
				pthread_mutex_unlock(doa->death_lock);
					doa->currentflag = 4;
				pthread_mutex_lock(doa->print_mutex);
					printf("%ld ms: %d is died\n", doa->m.tv_sec * 1000 + doa->m.tv_usec / 1000 - doa->time_birth, doa->numb_philo);
				pthread_mutex_unlock(doa->print_mutex);
				break;
			}

		}
	// if (*(doa->death_event) == 0)
	// 			return ;
	if(doa->currentflag < 3)
		doa->currentflag++;
	else if( doa->currentflag == 3)
		doa->currentflag = 1;
	
	// usleep(5);
}
