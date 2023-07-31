/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:48:38 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/31 12:16:42 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

int	deathchecker(t_philo *philo)
{
	int	i;

	i = 1;
	pthread_mutex_lock(philo->death_lock);
	pthread_mutex_lock(philo->eat_lock);
	gettimeofday(&(philo->m), &(philo->y));
	if (*philo->death_event == 0 && philo->time_round_death - ((philo->m).tv_sec
			* 1000 + (philo->m).tv_usec / 1000) >= philo->time_die)
	{
		*philo->death_event = 1;
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld ms: %d is died\n", philo->m.tv_sec * 1000 + philo->m.tv_usec
			/ 1000 - philo->time_birth, philo->numb_philo);
		pthread_mutex_unlock(philo->print_mutex);
	}
	if (*philo->death_event == 1 || (philo->meal_plan > 0
			&& *philo->meal_eaten == philo->meal_plan))
		i = 0;
	if (philo->individual_meal_plan > 0
		&& philo->individual_meal_eaten == philo->individual_meal_plan)
		i = 0;
	pthread_mutex_unlock(philo->death_lock);
	pthread_mutex_unlock(philo->eat_lock);
	return (i);
}

void	evenlife(t_philo *philos)
{
	if (philos->numb_philo % 2 == 0)
	{
		if (deathchecker(philos) == 0)
			return ;
		else if (philos->currentflag == 1)
		{
			eating(philos, 1);
			if (philos->currentflag == 2)
				activity(philos, &philos->counttime_sleep, &philos->time_sleep);
			if (philos->currentflag == 3)
				activity(philos, &philos->counttime_thinking,
					&philos->time_thinking);
		}
		else if (philos->currentflag == 4)
			return ;
	}
}

void	oddlife(t_philo *philos)
{
	if (philos->totoal_numb_philo == 1)
	{
		ft_usleep(philos->time_die, philos, 0, 0);
		return ;
	}
	if (philos->numb_philo % 2 != 0)
	{
		if (deathchecker(philos) == 0)
			return ;
		else if (philos->currentflag == 1)
		{
			eating(philos, 2);
			if (philos->currentflag == 2)
				activity(philos, &philos->counttime_sleep, &philos->time_sleep);
			if (philos->currentflag == 3)
				activity(philos, &philos->counttime_thinking,
					&philos->time_thinking);
		}
		else if (philos->currentflag == 4)
			return ;
	}
}

void	*routine(void *philo_invoid)
{
	t_philo	philo_rising;

	philo_rising = *(t_philo *)philo_invoid;
	while (deathchecker(&philo_rising) == 1)
	{
		evenlife(&philo_rising);
		oddlife(&philo_rising);
	}
	return ((void *)0);
}
