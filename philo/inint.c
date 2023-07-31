/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:48:07 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/31 12:29:51 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

void	inint_fork_placement(t_philo *dolist, t_fork *fork, int i)
{
	int	count;

	count = -1;
	while (++count < i)
	{
		(dolist + count)->right = (fork + count);
		if (count == 0 && i != 1)
			(dolist + count)->left = (fork + i - 1);
		else
			(dolist + count)->left = (fork + count - 1);
	}
	count = -1;
}

int	forkmanup(t_fork *forkes, int len, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		while (++i < len)
		{
			forkes[i].i = 1;
			forkes[i].forkid = i + 1;
			if (pthread_mutex_init(&((forkes[i].fork)), NULL) != 0)
				return (1);
		}
	}
	if (flag == 2)
		while (++i < len)
			if (pthread_mutex_destroy(&((forkes[i].fork))) != 0)
				return (1);
	if (flag == 3)
		if (pthread_mutex_destroy(&((forkes[i].fork))) != 0)
			return (1);
	return (0);
}

void	setdolist(t_philo *dolist, char *argc[], int i)
{
	int	status;

	dolist->totoal_numb_philo = ft_atoi(argc[1], &status, 1);
	dolist->numb_philo = i + 1;
	dolist->time_eat = ft_atoi(argc[3], &status, 1);
	dolist->time_sleep = ft_atoi(argc[4], &status, 1);
	dolist->time_die = ft_atoi(argc[2], &status, 1);
	if (dolist->time_eat == dolist->time_sleep)
		dolist->time_thinking = 0;
	else if (dolist->time_eat > dolist->time_sleep)
		dolist->time_thinking = (dolist->time_eat - dolist->time_sleep);
	else
		dolist->time_thinking = 0;
	if (argc[5])
	{
		dolist->meal_plan = atoi(argc[5]) * atoi(argc[1]);
		dolist->individual_meal_plan = atoi(argc[5]);
	}
	else
	{
		dolist->meal_plan = 0;
		dolist->individual_meal_plan = 0;
	}
	dolist->individual_meal_eaten = 0;
	dolist->meal_eaten = 0;
}

int	extra_mutex_init(pthread_mutex_t *printer_lock, pthread_mutex_t *death_lock,
		pthread_mutex_t *eat_lock, int flag)
{
	if (flag == 1)
	{
		if (pthread_mutex_init((printer_lock), NULL) != 0)
			return (1);
		if (pthread_mutex_init((death_lock), NULL) != 0)
			return (1);
		if (pthread_mutex_init((eat_lock), NULL) != 0)
			return (1);
	}
	if (flag == 2)
	{
		if (pthread_mutex_destroy((printer_lock)) != 0)
			return (1);
		if (pthread_mutex_destroy((death_lock)) != 0)
			return (1);
		if (pthread_mutex_destroy((eat_lock)) != 0)
			return (1);
	}
	return (0);
}

void	philo_utils_inint(t_philo *dolist, t_fork *forkes, char *argc[],
		int length)
{
	int				i;
	pthread_mutex_t	printer_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eat_lock;
	int				death;

	death = 0;
	i = -1;
	if (extra_mutex_init(&printer_lock, &death_lock, &eat_lock, 1) == 1)
		return ;
	inint_fork_placement(dolist, forkes, length);
	while (++i < length)
	{
		dolist[i].currentflag = 1;
		dolist[i].print_mutex = &printer_lock;
		dolist[i].death_lock = &death_lock;
		dolist[i].eat_lock = &eat_lock;
		setdolist(&(dolist[i]), argc, i);
	}
	starter(dolist, argc, death);
	if (extra_mutex_init(&printer_lock, &death_lock, &eat_lock, 2) == 1)
		return ;
}
