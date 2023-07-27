#include "Philosphers.h"

int deathchecker (to_do *philo)
{
	int i;

	i = 1;
	pthread_mutex_lock(philo->death_lock);
	pthread_mutex_lock(philo->eat_lock);
	if(*philo->death_event == 1 &&  ((philo->meal_plan > 0 && *philo->meal_eaten == philo->meal_plan )|| philo->meal_plan == 0))
	{
		i = 0;
	}
	pthread_mutex_unlock(philo->death_lock);
	pthread_mutex_unlock(philo->eat_lock);
	return (i);
}

void evenlife (to_do *philos)
{
    if (deathchecker(philos) == 0)
			return;

	if(philos->numb_philo % 2 == 0)
	{
		if ( philos->currentflag == 1 )
			eating(philos);
		else if ( philos->currentflag == 2)
			activity(philos, &philos->counttime_sleep, &philos->time_sleep);
		else if ( philos->currentflag == 3)
		{
			activity(philos, &philos->counttime_thinking, &philos->time_thinking);
					// philos->currentflag = 1;
		}	
		else if ( philos->currentflag == 4)
			return ;
	}
	else
	{
		int i;

		i = 0;
		if (philos->time_die > philos->time_eat )
		 	i = philos->time_eat;
		// printf("%d philo entered i: %d\n", philos->numb_philo,i);

		if (philos->time_die - (philos->time_eat + philos->time_sleep) > 0)
			i =philos->time_eat + philos->time_sleep;

		if (philos->time_die == philos->time_eat)
			i = 0  ;
		ft_usleep(i,philos);
		// usleep(i);
	} 
}

void oddlife (to_do *philos)
{
		// if (deathchecker(philos) == 0)
		// 	return;
		// printf("%d philo entered \n", philos->numb_philo);

	if(philos->numb_philo % 2 != 0)
	{
		if ( philos->currentflag == 1 )
		{
			eating(philos);
		}
		else if ( philos->currentflag == 2)
			activity(philos, &philos->counttime_sleep, &philos->time_sleep);
		else if ( philos->currentflag == 3)
		{
			activity(philos, &philos->counttime_thinking, &philos->time_thinking);
					// philos->currentflag = 1;
		}	
		else if ( philos->currentflag == 4)
			return ;
	}
}	

// void life( to_do *philos)
// {
// 	// if (deathchecker(philos) == 0)
// 	// {
// 	// 	return;
// 	// }
// 	evenlife(philos);
// 	oddlife(philos);
// }

void *routine( void *philo_invoid)
{
	to_do philo_rising;
	
	philo_rising = * (to_do *) philo_invoid;
	while (deathchecker(&philo_rising) == 1)
	{

	pthread_mutex_lock(philo_rising.eat_lock);
	if((philo_rising.meal_plan) != 0 && *philo_rising.meal_eaten == philo_rising.meal_plan)
	{
		pthread_mutex_unlock(philo_rising.eat_lock);
		break;
	}	
	else
		pthread_mutex_unlock(philo_rising.eat_lock);
	evenlife(&philo_rising);
	oddlife(&philo_rising);
	
	}
		// pthread_mutex_unlock(philo_rising.eat_lock);

	return (void *)0;
}
