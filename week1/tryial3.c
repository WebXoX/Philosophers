#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct t_neighbours
{
    to_do *past;
	to_do *present;
    to_do *future;
}       t_neighbours;
typedef struct to_do
{

	int			numb_philo;
	long int	time_birth;
	long int	time_current;
	int			time_eat;
	int			time_sleep;
	int			time_die;
	int			meal_plan;
    pthread_t	t;
	pthread_mutex_t m;
	t_neighbours test;

}				to_do;




to_do *ft_lst_last(to_do *dolist){
	int i;

	i = 0;
	while (dolist!=NULL)
	{
		dolist++;
		printf("hi");
	i++;
	}	
	i--;
	return(&*(dolist));
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

void	*timz()
{
    printf("hi thread here");
}
void* routine(void *test)
{
	t_neighbours wow;

	wow = * (t_neighbours*)test;
	print(*(wow.future));
}
void threads( to_do *dolist, int i)
{
	int count;
	count = -1;
	while (++count<i)
	{
		(dolist+ count)->test.present = &*(dolist + count);
		(dolist+ count)->test.future= &*(dolist +count + 1 );
		if(count == 0)
			(dolist+ count)->test.past = &*(dolist + i - 1);
		else
			(dolist+ count)->test.past = &*(dolist + count - 1);

		pthread_create(&dolist->t,NULL,&routine,&((dolist+ count)->test));
	}
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

	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof( to_do)*(atoi(argc[1])));
		i = -1;
		gettimeofday (&m, &y);
		while (++i < argv - 1)
		{
			setdolist(&(dolist[i]), argc, i);
			dolist[i].time_birth = m.tv_usec / 1000;
			// print((dolist[i]));
		}
		threads(dolist,atoi(argc[1]));
	}
}
