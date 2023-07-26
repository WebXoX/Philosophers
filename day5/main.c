/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:29:34 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/26 09:31:06 by jperinch         ###   ########.fr       */
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

int main (int argv, char *argc[])
{
	to_do			*dolist;
	t_fork			*forkes;

	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof(to_do)*(atoi(argc[1])));
        forkes = malloc(sizeof(t_fork)*(atoi(argc[1])));
		if(forkmanup(forkes,atoi(argc[1]),1) == 1)
			return 1;

	    philo_utils_inint( dolist,  forkes,argc, atoi(argc[1]));
		// printf("ms: ");
		

		if (forkmanup(forkes,atoi(argc[1]),2) == 1)
			return 1;

		free(forkes);
		free(dolist);
	}
}
