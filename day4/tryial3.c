#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct t_fork
{
	pthread_mutex_t fork;
	int				i;
}				t_fork;

typedef struct to_do
{

	int				numb_philo;
	long int		time_birth;
	long int		time_current;
	long int		time_eat;
	long int		time_sleep;
	long int		time_thinking;
	long int		time_die;
	long int		counttime_eat;
	long int		counttime_sleep;
	long int		counttime_thinking;
	long int		counttime_die;
	int 			currentflag;
	int				meal_plan;
	int				lifecycle;
    pthread_t		t;
	t_fork			*left;
	t_fork			*right;
	struct timeval 	m;
	struct timezone y;
}				to_do;

void	timed( to_do * doa, long int *count )
{
		gettimeofday(&(doa->m), &(doa->y));
		*count =  (doa->m).tv_usec  - (doa->time_birth);
		while(doa->counttime_eat < doa->time_eat){
			gettimeofday(&(doa->m), &(doa->y));
			*count =  (doa->m).tv_usec  - (doa->time_birth);
			// printf("\n%ld\n",*count/1000);
		}
}

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
	printf("time_eat: %ld\n", dolist.time_eat);
	printf("time_sleep: %ld\n", dolist.time_sleep);
	printf("time_die: %ld\n", dolist.time_die);
	printf("meal_plan: %d", dolist.meal_plan);
	printf("\n-----------------------------\n");
}

void	*timz()
{
    printf("hi thread here");
	return 0;
}

void statusprint(to_do *dolist)
{
	printf("\n\ni:%d\n",dolist->currentflag);

	printf("\n%ld ms: ", dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth);
	if (dolist->currentflag == 1)
	{
		printf("%d has taken a fork\n", dolist->numb_philo);
		printf("%ld ms: %d has taken a fork\n",(dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth), dolist->numb_philo);
		printf("%ld ms: %d is eating",dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth,  dolist->numb_philo);
	}
	if (dolist->currentflag == 2)
		printf("%d is sleeping", dolist->numb_philo);
	if (dolist->currentflag == 3)
		printf("%d is thinking", dolist->numb_philo);
	if (dolist->currentflag == 4)
		printf("%d is died", dolist->numb_philo);
}

void activity(  to_do * doa, long int *count,long int *limit  )
{
	gettimeofday(&(doa->m), &(doa->y));
	// doa->currentflag = 1;
	statusprint(doa);
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_birth);
		while( *count < *limit){
			gettimeofday(&(doa->m), &(doa->y));
			*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_birth);
		}
}

void* routine(void *test)
{
	to_do wow;

	wow = * (to_do*)test;
	// printf("i:%d\n\n",wow.currentflag);
		// printf("left:: %d\n\n",wow.right->i);
	if(wow.currentflag == 1)
	{
		pthread_mutex_lock(&wow.right->fork);
		pthread_mutex_lock(&wow.left->fork);
		printf("\n%d : do %d\n",wow.numb_philo, ((wow.right->i)));
		if(wow.right->i == 1 && wow.left->i == 1)
		{
		printf("%d : do %d\n",wow.numb_philo, ((wow.right->i)));
		
			wow.right->i--;
			wow.left->i--; 
			pthread_mutex_unlock(&wow.right->fork);
			pthread_mutex_unlock(&wow.left->fork);
			activity(&wow, &wow.counttime_eat, &wow.time_eat);
			pthread_mutex_lock(&wow.right->fork);
			pthread_mutex_lock(&wow.left->fork);
			wow.right->i++;
			wow.left->i++;
			pthread_mutex_unlock(&wow.right->fork);
			pthread_mutex_unlock(&wow.left->fork);
		}
		else
		{
			printf("hitherersadf as\n");
			usleep(10);
		}
	}
	if(wow.currentflag == 2)
		activity(&wow, &wow.counttime_sleep, &wow.time_sleep);
	if(wow.currentflag == 3)
		activity(&wow, &wow.counttime_thinking, &wow.time_thinking);
	if(wow.currentflag== 4)
	{
		activity(&wow, &wow.counttime_die, &wow.time_die);
		
	}
	// printf("eating :%ld\n",wow.counttime_eat);
	// printf("\nend-----------------\n\n");3
	return (void *)0;
}

void threads( to_do *dolist, t_fork *fork, int i)
{
	int count;

	count = -1;
	while (++count<i)
	{
		

		if(count + 1  == i)
{
			(dolist + count)->right = (fork);
		// printf("%d : forkes %d\n",count+1, ((fork)->i));
		// printf("%d : do %d\n",count+1, ((dolist+count)->right->i));

}
		else
{			(dolist+ count)->right = (fork +count  );
		// printf("%d : forkes %d\n",count+1, ((fork+count)->i));
		// printf("%d : do %d\n",count+1, ((dolist+count)->right->i));

}
		if(count == 0)
		{
			(dolist+ count)->left = (fork + i - 1);
		// // printf("%d : forkes %d\n",count+1, ((fork+i-1)->i));
		// printf("%d : do %d\n",count+1, ((dolist+count)->left->i));

		
		}
		else{
			(dolist+ count)->left = (fork + count - 1);
		// printf("%d : forkes %d\n",count+1, ((fork+count -1)->i));
		// printf("%d : do %d\n",count+1, ((dolist+count)->left->i));


		}

		// printf("%d : forkes %d\n",count+1, ((fork+count)->i));
		// printf("%d : forkes %d\n",count+1, ((fork+count-1)->i));
		// if (pthread_mutex_init(&(dolist+count)->fork,NULL) != 0)
		// 		return  ;
		// printf("\nstarting of thread %d\n",(dolist + count)->numb_philo);
		// if (pthread_create(&(dolist+count)->t,NULL,&routine,((dolist+ count))) != 0)
		// 		return  ;
	}
	count = -1;
	// while (++count < i)
	// {
	// 	pthread_join((dolist + count)->t,NULL);
	// 	// if (pthread_mutex_destroy(&(dolist+count)->fork) != 0)
	// 	// 		return  ;
	// 	printf("\nend of thread %d",(dolist+count)->numb_philo);
	// }
}


int forkmanup(t_fork *forkes, int len, int flag)
{
	int i;

	i = -1;
	if ( flag == 1)
	while (++i < len)
	{
		forkes[i].i=1;
		if(pthread_mutex_init(&((forkes[i].fork)),NULL) != 0)
			return (1);

	}
	if ( flag == 2)
		while (++i < len)
			if(pthread_mutex_destroy(&((forkes[i].fork))) != 0)
				return (1);
	return (0);
}

int	main(int argv, char *argc[])
{
	to_do			*dolist;
	t_fork			*forkes;
	int				i;
	struct timeval	m;
	struct timezone	y;

	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof( to_do)*(atoi(argc[1])));
        forkes = malloc(sizeof( t_fork)*(atoi(argc[1])));
		i = -1;
		
			gettimeofday(&(m), &(y));
		if(forkmanup(forkes,atoi(argc[1]),1) == 1)
			return(0);
		
		threads(dolist,forkes,atoi(argc[1]));
		while (++i < atoi(argc[1]) )
		{
		// printf("%d : forkes %d\n",i+1, ((dolist+i)->right->i));
		// // printf("forkes %d\n", (forkes+i+1)->i);
		// }
			dolist[i].currentflag = 1;
			setdolist(&(dolist[i]), argc, i);
			dolist[i].time_birth = m.tv_sec * 1000 + m.tv_usec/1000 ;
			// printf("\n%ld",dolist[i].time_birth);
			// print((dolist[i]));
			if (pthread_create(&(dolist+i)->t,NULL,&timz,((dolist+ i))) != 0)
				return 0 ;
		}
		i=-1;
		while (++i < atoi(argc[1]))
		{
		pthread_join((dolist + i)->t,NULL);
		// if (pthread_mutex_destroy(&(dolist+count)->fork) != 0)
		// 		return  ;
		printf("\nend of thread %d",(dolist+i)->numb_philo);
		}
			if(forkmanup(forkes,atoi(argc[1]),2) == 1)
			{
				return(0);
			// printf("hi");
			}
		free(forkes);
		free(dolist);
	}
}
