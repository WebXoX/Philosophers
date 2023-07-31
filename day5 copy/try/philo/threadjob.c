#include "Philosphers.h"

int deathchecker (to_do *philo)
{
	int i;

	i = 1;
	pthread_mutex_lock(philo->death_lock);
	pthread_mutex_lock(philo->eat_lock);
	if(*philo->death_event == 1 || (philo->meal_plan > 0 && *philo->meal_eaten == philo->meal_plan ))
		i = 0;
	if (philo->individual_meal_plan > 0 &&philo->individual_meal_eaten == philo->individual_meal_plan )
		i = 0;
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
		{
			eating(philos);
			if ( philos->currentflag == 2 )
				activity(philos, &philos->counttime_sleep, &philos->time_sleep);
		}
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
		// if( philos->time_eat != philos->time_sleep)
			ft_usleep(1,philos);
	}
}

void oddlife (to_do *philos)
{
	if (philos->totoal_numb_philo == 1)
	{
		printf("hi");
		ft_usleep(philos->time_die,philos);
	}
	if(philos->numb_philo % 2 != 0)
	{
		if (deathchecker(philos) == 0)
			return;
		else if ( philos->currentflag == 1 )
			eating2(philos);
		else if ( philos->currentflag == 2)
			activity(philos, &philos->counttime_sleep, &philos->time_sleep);
		else if ( philos->currentflag == 3)
		{
			activity(philos, &philos->counttime_thinking, &philos->time_thinking);
		}
		else if ( philos->currentflag == 4)
			return ;
	}
	else
	{
		// if( philos->time_eat != philos->time_sleep)
			ft_usleep(1,philos);
	}
}

void *routine( void *philo_invoid)
{
	to_do philo_rising;

	philo_rising = * (to_do *) philo_invoid;
	while (deathchecker(&philo_rising) == 1)
	{
		oddlife(&philo_rising);
		evenlife(&philo_rising);
	
	}
	return (void *)0;
}
