#include "Philosphers.h"

void mutex_events(to_do *philos, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(&philos->left->fork);
		philos->left->i = 0;
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_lock(&philos->right->fork);
		philos->right->i = 0;
		*(philos->meal_eaten)+=1;
		pthread_mutex_unlock(&philos->right->fork);
	}
	if (flag == 2)
	{
		pthread_mutex_lock(&philos->left->fork);
		philos->left->i = 1;
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_lock(&philos->right->fork);
		philos->right->i = 1;
		pthread_mutex_unlock(&philos->right->fork);
	}
	// if (flag == 3)
	// 		pthread_mutex_lock(print);
	// if (flag == 4)
	// 		pthread_mutex_unlock(print);

}