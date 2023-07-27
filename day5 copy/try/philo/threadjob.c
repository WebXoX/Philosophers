#include "Philosphers.h"

int deathchecker (to_do *philo)
{
	int i;

	i = 1;
	pthread_mutex_lock(philo->death_lock);
	pthread_mutex_lock(philo->eat_lock);
	if(*philo->death_event == 1 ||  ((philo->meal_plan > 0 && *philo->meal_eaten == philo->meal_plan )))
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
		if (deathchecker(philos) == 0)
			return;

		else if ( philos->currentflag == 1 )
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
		ft_usleep(5,philos);
	}
}

void oddlife (to_do *philos)
{
		if (deathchecker(philos) == 0)
			return;
		// printf("%d philo entered \n", philos->numb_philo);

	if(philos->numb_philo % 2 != 0)
	{
		if (deathchecker(philos) == 0)
			return;
		else if ( philos->currentflag == 1 )
		{
			eating2(philos);
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
	else
	{
		ft_usleep(5,philos);
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

	// pthread_mutex_lock(philo_rising.eat_lock);
	// if((philo_rising.meal_plan) != 0 && *philo_rising.meal_eaten == philo_rising.meal_plan)
	// {
	// 	pthread_mutex_unlock(philo_rising.eat_lock);
	// 	break;
	// }
	// else
	// 	pthread_mutex_unlock(philo_rising.eat_lock);
	// printf("%d death: philo %d\n",*philo_rising.death_event, philo_rising.numb_philo);
	evenlife(&philo_rising);
	oddlife(&philo_rising);


	}
		// pthread_mutex_unlock(philo_rising.eat_lock);
	printf("%d death: philo %d\n",*philo_rising.death_event, philo_rising.numb_philo);

	return (void *)0;
}
