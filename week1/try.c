#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>

typedef struct to_do
{
	int			numb_philo;
	long int	time_birth;
	long int	time_current;
	int			time_eat;
	int			time_sleep;
	int			time_die;
	int			meal_plan;

}				to_do;

// typedef struct t_time
// {
//     timeval *current_time;
//     timezone *zone;
// }       t_time;

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
void	setdolist(to_do *dolist, char *argc[], int i)
{
	dolist->numb_philo = i+1;
	dolist->time_eat = atoi(argc[2]);
	dolist->time_sleep = atoi(argc[3]);
	dolist->time_die = atoi(argc[4]);
	if (argc[5])
		dolist->meal_plan = atoi(argc[5]);
	else
		dolist->meal_plan = 0;
}

void	print(to_do dolist)
{
	printf("\n_____________________________");
	printf("\nnumb_philo:%d\n", dolist.numb_philo);
	printf("philo_birth_time:%ld\n", dolist.time_birth);
	printf("time_eat: %d\n", dolist.time_eat);
	printf("time_sleep: %d\n", dolist.time_sleep);
	printf("time_die: %d", dolist.time_die);
	printf("\nmeal_plan: %d", dolist.meal_plan);
	printf("\n-----------------------------\n");
}

void	timed(long int *time, struct timeval m, struct timezone y)
{
	gettimeofday(&m, &y);
	*time = m.tv_usec / 1000;
}

int	main(int argv, char *argc[])
{
	to_do			*dolist;
	int				i;
	struct timeval	m;
	struct timezone	y;

	// t_time mtime;
	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof( to_do)*argv-1);
        // dolist[argv-1] =NULL;
		i = -1;
		gettimeofday(&m, &y);
		while (++i < argv-1)
		{
			setdolist(&(dolist[i]), argc, i);
			dolist[i].time_birth = m.tv_usec / 1000;
			print((dolist[i]));
		}
        free(dolist);
		// timed(&dolist.time_birth,m,y);
		// // for(int i =0; i <100000;i++){
		// // printf("%ld :%d\n",dolist.time_birth,i);
		// // }
		// timed(&dolist.time_current,m,y);
		// printf("%ld\n",dolist.time_birth);
		// printf("%ld\n",dolist.time_current);
		// printf("%ld\n",dolist.time_current-dolist.time_birth);
	}
}
