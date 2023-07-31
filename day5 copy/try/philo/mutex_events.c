// #include "Philosphers.h"

// void mutex_events(to_do *philos, int flag)
// {
// 	if (flag == 1)
// 	{
// 		pthread_mutex_lock(&philos->left->fork);
// 		philos->left->i = 0;
// 		pthread_mutex_unlock(&philos->left->fork);
// 		pthread_mutex_lock(&philos->right->fork);
// 		philos->right->i = 0;
// 		pthread_mutex_unlock(&philos->right->fork);
// 		pthread_mutex_lock(philos->eat_lock);
// 		*(philos->meal_eaten)+=1;
// 		pthread_mutex_unlock(philos->eat_lock);

// 	}
// 	if (flag == 2)
// 	{
// 		pthread_mutex_lock(&philos->left->fork);
// 		philos->left->i = 1;
// 		pthread_mutex_unlock(&philos->left->fork);
// 		pthread_mutex_lock(&philos->right->fork);
// 		philos->right->i = 1;
// 		pthread_mutex_unlock(&philos->right->fork);
// 	}
// 	// if (flag == 3)
// 	// 		pthread_mutex_lock(print);
// 	// if (flag == 4)
// 	// 		pthread_mutex_unlock(print);

// }

#include "Philosphers.h"

void mutex_events(to_do *philos, int flag)
{

		flag =2 + flag;
		// int i;
		// pthread_mutex_lock(philos->print_mutex);
		// printf("hi");
		// pthread_mutex_unlock(philos->print_mutex);
	pthread_mutex_lock(&philos->right->fork);
	pthread_mutex_lock(&philos->left->fork);
	if(philos->right->i == 1 && philos->left->i == 1)
		{
			philos->left->i = 0;
			pthread_mutex_unlock(&philos->left->fork);
			philos->right->i = 0;
			pthread_mutex_unlock(&philos->right->fork);
			gettimeofday(&(philos->m), &(philos->y));
			philos->counttime_die = 0;
			philos->time_round_death = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000;
			activity(philos, &philos->counttime_eat, &philos->time_eat);
			pthread_mutex_lock(philos->eat_lock);
			*(philos->meal_eaten)+=1;
			philos->individual_meal_eaten += 1;
			pthread_mutex_unlock(philos->eat_lock);
			pthread_mutex_lock(&philos->right->fork);
			philos->right->i = 1;
			pthread_mutex_unlock(&philos->right->fork);
			pthread_mutex_lock(&philos->left->fork);
			philos->left->i = 1;
			pthread_mutex_unlock(&philos->left->fork);
	}
	else
	{
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_unlock(&philos->right->fork);
	// }
		// pthread_mutex_lock(philos->print_mutex);
		// printf("hi");
		// pthread_mutex_unlock(philos->print_mutex);


		if (philos->time_die > philos->time_eat )
			ft_usleep(1,philos);
		if (philos->time_die == philos->time_eat)
			ft_usleep(0,philos);
	}

}

void mutex_events2(to_do *philos, int flag)
{

		flag =2 + flag;
		// int i;
	pthread_mutex_lock(&philos->left->fork);
	pthread_mutex_lock(&philos->right->fork);
	if(philos->left->i == 1 && philos->right->i == 1)
		{
			philos->right->i = 0;
			pthread_mutex_unlock(&philos->right->fork);
			philos->left->i = 0;
			pthread_mutex_unlock(&philos->left->fork);
			gettimeofday(&(philos->m), &(philos->y));
			philos->counttime_die = 0;
			philos->time_round_death = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000;
			activity(philos, &philos->counttime_eat, &philos->time_eat);
			pthread_mutex_lock(philos->eat_lock);
			*(philos->meal_eaten) += 1;
			philos->individual_meal_eaten += 1;
			pthread_mutex_unlock(philos->eat_lock);
			pthread_mutex_lock(&philos->left->fork);
			pthread_mutex_lock(&philos->right->fork);
			philos->left->i = 1;
			philos->right->i = 1;
			pthread_mutex_unlock(&philos->right->fork);
			pthread_mutex_unlock(&philos->left->fork);
	}
	else
	{
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_unlock(&philos->right->fork);
		//  		pthread_mutex_lock(philos->print_mutex);
		// printf("hi");
		// pthread_mutex_unlock(philos->print_mutex);
		// if (philos->time_die > philos->time_eat )
		//  	i =  philos->time_eat;
		// if (philos->time_die == philos->time_eat)
		// 	i = 0  ;
		if (philos->time_eat > philos->time_sleep )
			ft_usleep(1,philos);
		if (philos->time_die == philos->time_eat)
			ft_usleep(0,philos);
	}

}