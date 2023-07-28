/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:29:34 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/28 12:48:13 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

int starter(to_do *dolist , char *argc[], int death)
{

	struct timeval	m;
	struct timezone	y;
	int i;
	int meal;

	meal = 0;
	i = -1;
	gettimeofday(&(m), &(y));
	while (++i < atoi(argc[1]) )
	{
		dolist[i].time_birth = m.tv_sec * 1000 + m.tv_usec/1000 ;
		dolist[i].time_round = m.tv_sec * 1000 + m.tv_usec/1000 ;
		dolist[i].time_round_death = m.tv_sec * 1000 + m.tv_usec/1000 ;
		dolist[i].death_event = &death;
		dolist[i].meal_eaten = &meal;
		if (pthread_create(&(dolist+i)->t,NULL,&routine,((dolist+ i))) != 0)
			return 1;
	}
	i = -1;
	while (++i < atoi(argc[1]))
		if (pthread_join((dolist + i)->t,NULL) != 0)
			return 1;
    return 0;
}

int	checker(char *ptr[])
{
	int	i;
	int	j;

	i = 0;
	while ((ptr[++i]))
	{
		j = -1;
		while (ptr[i][++j])
			if (!((ptr[i][j]) >= '0' && (ptr[i][j]) <= '9'))
				return (0);
	}
	return (1);
}

int main (int argc, char *argv[])
{
	to_do			*dolist;
	t_fork			*forkes;
	int status;

	if ((argc == 5 || argc == 6) && checker(argv) == 1)
	{
		if (ft_atoi(argv[1],&status,1) <= 0  || ft_atoi(argv[2],&status,1) <= 0 || ft_atoi(argv[3],&status,1) <= 0)
			return 0;
		
        dolist = malloc(sizeof(to_do)*(atoi(argv[1])));
        forkes = malloc(sizeof(t_fork)*(atoi(argv[1])));
		if(forkmanup(forkes,ft_atoi(argv[1],&status,1),1) == 1)
			return 1;
	    philo_utils_inint( dolist,  forkes,argv, atoi(argv[1]));
		if (forkmanup(forkes,atoi(argv[1]),2) == 1)
			return 1;
		free(forkes);
		free(dolist);
	}
}
