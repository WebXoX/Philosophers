/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:48:29 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/31 12:37:07 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

void	meal_counter(t_philo *philos)
{
	pthread_mutex_lock(philos->eat_lock);
	*(philos->meal_eaten) += 1;
	philos->individual_meal_eaten += 1;
	pthread_mutex_unlock(philos->eat_lock);
	pthread_mutex_lock(&philos->right->fork);
	philos->right->i = 1;
	pthread_mutex_unlock(&philos->right->fork);
	pthread_mutex_lock(&philos->left->fork);
	philos->left->i = 1;
	pthread_mutex_unlock(&philos->left->fork);
}

void	mutex_events(t_philo *philos)
{
	pthread_mutex_lock(&philos->right->fork);
	pthread_mutex_lock(&philos->left->fork);
	if (philos->right->i == 1 && philos->left->i == 1)
	{
		philos->left->i = 0;
		pthread_mutex_unlock(&philos->left->fork);
		philos->right->i = 0;
		pthread_mutex_unlock(&philos->right->fork);
		gettimeofday(&(philos->m), &(philos->y));
		philos->counttime_die = 0;
		philos->time_round_death = (philos->m).tv_sec * 1000
			+ (philos->m).tv_usec / 1000;
		activity(philos, &philos->counttime_eat, &philos->time_eat);
		meal_counter(philos);
	}
	else
	{
		if (philos->totoal_numb_philo % 2 == 1
			&& philos->numb_philo % 2 == 1
			&& philos->time_eat == philos->time_sleep && philos->time_die
			- philos->counttime_die < philos->time_eat)
			ft_usleep(philos->time_die - philos->counttime_die, philos, 0, 0);
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_unlock(&philos->right->fork);
	}
}

void	mutex_events2(t_philo *philos)
{
	pthread_mutex_lock(&philos->left->fork);
	pthread_mutex_lock(&philos->right->fork);
	if (philos->left->i == 1 && philos->right->i == 1)
	{
		philos->right->i = 0;
		pthread_mutex_unlock(&philos->right->fork);
		philos->left->i = 0;
		pthread_mutex_unlock(&philos->left->fork);
		gettimeofday(&(philos->m), &(philos->y));
		philos->counttime_die = 0;
		philos->time_round_death = (philos->m).tv_sec * 1000
			+ (philos->m).tv_usec / 1000;
		activity(philos, &philos->counttime_eat, &philos->time_eat);
		meal_counter(philos);
	}
	else
	{
		if (philos->totoal_numb_philo % 2 == 1
			&& philos->numb_philo % 2 == 1
			&& philos->time_eat == philos->time_sleep && philos->time_die
			- philos->counttime_die < philos->time_eat)
			ft_usleep(philos->time_die - philos->counttime_die, philos, 0, 0);
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_unlock(&philos->right->fork);
	}
}
