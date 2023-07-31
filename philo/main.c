/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:29:34 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/31 12:17:01 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

int	starter(t_philo *dolist, char *argc[], int death)
{
	struct timeval	m;
	struct timezone	y;
	int				i;
	int				meal;

	meal = 0;
	i = -1;
	gettimeofday(&(m), &(y));
	while (++i < atoi(argc[1]))
	{
		dolist[i].time_birth = m.tv_sec * 1000 + m.tv_usec / 1000;
		dolist[i].time_round = m.tv_sec * 1000 + m.tv_usec / 1000;
		dolist[i].time_round_death = m.tv_sec * 1000 + m.tv_usec / 1000;
		dolist[i].death_event = &death;
		dolist[i].meal_eaten = &meal;
		if (pthread_create(&(dolist + i)->t, NULL, &routine, ((dolist
						+ i))) != 0)
			return (1);
	}
	i = -1;
	while (++i < atoi(argc[1]))
		if (pthread_join((dolist + i)->t, NULL) != 0)
			return (1);
	return (0);
}

int	checker(char *argv[])
{
	int	status;

	status = 0;
	if (ft_atoi(argv[1], &status, 1) <= 0 || ft_atoi(argv[2], &status, 1) <= 0
		|| ft_atoi(argv[3], &status, 1) <= 0 || ft_atoi(argv[4], &status,
			1) <= 0)
		return (1);
	if (argv[5] && ft_atoi(argv[5], &status, 1) <= 0)
		return (1);
	if (status == 1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	*dolist;
	t_fork	*forkes;
	int		status;

	status = 0;
	if ((argc == 5 || argc == 6) && checker(argv) == 0)
	{
		dolist = malloc(sizeof(t_philo) * (ft_atoi(argv[1], &status, 1)));
		forkes = malloc(sizeof(t_fork) * (ft_atoi(argv[1], &status, 1)));
		if (!dolist || !forkes)
			return (1);
		if (forkmanup(forkes, ft_atoi(argv[1], &status, 1), 1) == 1)
			return (1);
		philo_utils_inint(dolist, forkes, argv, ft_atoi(argv[1], &status, 1));
		if (forkmanup(forkes, atoi(argv[1]), 2) == 1)
			return (1);
		free(forkes);
		free(dolist);
	}
	else
		printf("INVALID ARGUMENTS");
}
