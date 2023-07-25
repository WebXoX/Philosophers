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
	long int		time_round;
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
	int 			*death_event;
	int				meal_plan;
	// int				lifecycle;
    pthread_t		t;
	t_fork			*left;
	t_fork			*right;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *death_lock;
	struct timeval 	m;
	struct timezone y;
}				to_do;



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
	dolist->time_eat = atoi(argc[3]);
	dolist->time_sleep = atoi(argc[4]);
	dolist->time_die = atoi(argc[2]);
	dolist->time_thinking = dolist->time_die -dolist->time_eat + dolist->time_sleep;

	if(dolist->time_thinking < 0)
		dolist->time_thinking = 0;

	if (argc[5])
		dolist->meal_plan = atoi(argc[5]);
	else
		dolist->meal_plan = 0;
}

void	print(to_do dolist)
{
	pthread_mutex_lock(dolist.print_mutex);

	printf("\n_____________________________");
	printf("\nnumb_philo:%d\n", dolist.numb_philo);
	printf("philo_birth_time:%ld\n", dolist.time_birth);
	printf("time_eat: %ld\n", dolist.time_eat);
	printf("time_sleep: %ld\n", dolist.time_sleep);
	printf("time_die: %ld\n", dolist.time_die);
	printf("meal_plan: %d", dolist.meal_plan);
	printf("\n-----------------------------\n");
	pthread_mutex_lock(dolist.print_mutex);

}
void mutex_events(pthread_mutex_t *left,pthread_mutex_t *right, pthread_mutex_t *print, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(left);
		pthread_mutex_lock(right);
	}
	if (flag == 2)
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
	}
	if (flag == 3)
			pthread_mutex_lock(print);
	if (flag == 4)
			pthread_mutex_unlock(print);

}

void statusprint(to_do *dolist)
{
	mutex_events(&dolist->left->fork,&dolist->right->fork,dolist->print_mutex,3);
	// pthread_mutex_lock(&dolist->print_mutex);

	if( *(dolist->death_event) != 1)
	{	
			printf("%ld ms: ", dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth);
	if (dolist->currentflag == 1)
	{
		printf("%d has taken a fork\n", dolist->numb_philo);
		printf("%ld ms: %d has taken a fork\n",(dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth), dolist->numb_philo);
		printf("%ld ms: %d is eating\n",dolist->m.tv_sec * 1000 + dolist->m.tv_usec / 1000 - dolist->time_birth,  dolist->numb_philo);
	}
	if (dolist->currentflag == 2)
		printf("%d is sleeping\n", dolist->numb_philo);
	if (dolist->currentflag == 3)
		printf("%d is thinking\n", dolist->numb_philo);
	}
	mutex_events(&dolist->left->fork,&dolist->right->fork,dolist->print_mutex,4);

	// pthread_mutex_unlock(&dolist->print_mutex);

}

void activity(  to_do * doa, long int *count,long int *limit  )
{
	gettimeofday(&(doa->m), &(doa->y));
	
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_round);
		statusprint(doa);
		while( *count < *limit)
		{
			gettimeofday(&(doa->m), &(doa->y));
			*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_birth);
			doa->counttime_die = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round);
		
			pthread_mutex_lock(doa->death_lock);
			if (doa->counttime_die >= doa->time_die && 	*(doa->death_event) ==0)
			{
			pthread_mutex_unlock(doa->death_lock);

				*(doa->death_event) = 1;
				doa->currentflag = 4;
			pthread_mutex_lock(doa->print_mutex);
				printf("%ld ms: %d is died\n", doa->m.tv_sec * 1000 + doa->m.tv_usec / 1000 - doa->time_birth, doa->numb_philo);
			pthread_mutex_unlock(doa->print_mutex);
				break;
			}
			else if (	*(doa->death_event) == 1)
				break;
		}
	
	if(doa->currentflag < 3)
		doa->currentflag++;
	else if( doa->currentflag != 4)
		doa->currentflag = 1;
	
	usleep(5);
}

void events( to_do *philos)
{
	
	// mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,3);
		// mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,1);
	if(philos->currentflag == 1 && *philos->death_event != 1)
	{
		if(philos->right->i == 1 && philos->left->i == 1)
		{
			// mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
			// if (philos->right->i == 0 || philos->left->i == 0 )
			// 	usleep(100);
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,1);
			gettimeofday(&(philos->m), &(philos->y));
			philos->counttime_die = 0;
			philos->counttime_die = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000  - (philos->time_round);

				philos->right->i--;
				philos->left->i--; 
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
				activity(philos, &philos->counttime_eat, &philos->time_eat);
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,1);
				philos->right->i++;
				philos->left->i++;
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
		}
		else
		{
			// printf("philo %d: flag: %d\n",philos->numb_philo,philos->currentflag);
			usleep(philos->counttime_eat);
		
		}
	}
	// if(philos->currentflag == 2 && *philos->death_event != 1)
	// {
	// 		// mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
	// 	activity(philos, &philos->counttime_sleep, &philos->time_sleep);
	// }
	// if(philos->currentflag == 3 && *philos->death_event != 1)
	// {
	// 		// mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
	// 	activity(philos, &philos->counttime_thinking, &philos->time_thinking);
	// }
		// statusprint(philos);
	// if(philos->currentflag== 4 && *philos->death_event != 1)
	// {
	// 	activity(philos, &philos->counttime_die, &philos->time_die);
	// }
	// mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,4);


}

void* routine(void *test)
{
	to_do wow;

	wow = * (to_do*)test;
	while (1)
	{
		// usleep(1);
	// pthread_mutex_lock(&wow.print_mutex);
	// printf("\n philosphers %d  starting:: %d\n",wow.numb_philo, ((wow.right->i)));
	// // print(wow);
	// pthread_mutex_unlock(&wow.print_mutex);
	if(*(wow.death_event)==1)
		break;

		events(&wow);
		// break;
	
	// pthread_mutex_lock(&wow.print_mutex);
	// // print(wow);
	// printf("\n philosphers %d ending:: %d\n",wow.numb_philo, ((wow.right->i)));
	// pthread_mutex_unlock(&wow.print_mutex);

		// break;
	}
	return (void *)0;
}

void threads( to_do *dolist, t_fork *fork, int i)
{
	int count;

	count = -1;
	while (++count<i)
	{
		// pthread_mutex_init(&(dolist + count)->print_mutex,NULL);
			(dolist+ count)->right = (fork +count  );
		if(count == 0)
			(dolist+ count)->left = (fork + i - 1);
		else
			(dolist+ count)->left = (fork + count - 1);
	}
	count = -1;
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
	if ( flag == 3)
		if(pthread_mutex_destroy(&((forkes[i].fork))) != 0)
				return (1);
	return (0);
}
void philo_utils_inint(to_do dolist[], t_fork *forkes, char* argc[],int length)
{
	int i;

	i = -1;

	if(forkmanup(forkes,length,1) == 1)
			return;
	threads(dolist,forkes,length);
	while (++i < length)
	{
			dolist[i].currentflag = 1;
			setdolist(&(dolist[i]), argc, i);
	}
}

int main (int argv, char *argc[])
{
	to_do			*dolist;
	t_fork			*forkes;
	pthread_mutex_t printer_lock;
	pthread_mutex_t death_lock;
	struct timeval	m;
	struct timezone	y;
	int i;
	int death;

	death = 0;
	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof(to_do)*(atoi(argc[1])));
        forkes = malloc(sizeof(t_fork)*(atoi(argc[1])));
		i = -1;
		if(pthread_mutex_init(&(printer_lock),NULL) != 0 && pthread_mutex_init(&(death_lock),NULL))
			return (1);
		gettimeofday(&(m), &(y));
		philo_utils_inint( dolist,  forkes,argc, atoi(argc[1]));
		while (++i < atoi(argc[1]) )
		{
			dolist[i].time_birth = m.tv_sec * 1000 + m.tv_usec/1000 ;
			dolist[i].time_round = m.tv_sec * 1000 + m.tv_usec/1000 ;
			dolist[i].print_mutex = &printer_lock;
			dolist[i].death_lock = &death_lock;
			dolist[i].death_event = &death;
			if (pthread_create(&(dolist+i)->t,NULL,&routine,((dolist+ i))) != 0)
				return 0 ;
		}
		i = -1;
		while (++i < atoi(argc[1]))
			if (pthread_join((dolist + i)->t,NULL) != 0)
				return 0 ;
		if (forkmanup(forkes,atoi(argc[1]),2) == 1)
			return(0);
		free(forkes);
		free(dolist);
	}
}


// int	main(int argv, char *argc[])
// {
// 	to_do			*dolist;
// 	t_fork			*forkes;
// 	pthread_mutex_t print;
// 	int				i;
// 	struct timeval	m;
// 	struct timezone	y;

// 	pthread_mutex_init(&print,NULL);
// 	if ((argv == 5 || argv == 6) && checker(argc) == 1)
// 	{
//         dolist = malloc(sizeof( to_do)*(atoi(argc[1])));
//         forkes = malloc(sizeof( t_fork)*(atoi(argc[1])));
// 		i = -1;
		
// 		gettimeofday(&(m), &(y));
// 		if(forkmanup(forkes,atoi(argc[1]),1) == 1)
// 			return(0);
		
// 		threads(dolist,forkes,atoi(argc[1]));
// 		while (++i < atoi(argc[1]) )
// 		{
// 			dolist[i].currentflag = 1;
// 			setdolist(&(dolist[i]), argc, i);
// 			dolist[i].time_birth = m.tv_sec * 1000 + m.tv_usec/1000 ;
// 			if (pthread_create(&(dolist+i)->t,NULL,&routine,((dolist+ i))) != 0)
// 				return 0 ;
// 		}
// 		i = -1;
// 		while (++i < atoi(argc[1]))
// 		{
// 			if (pthread_join((dolist + i)->t,NULL) != 0)
// 				return 0 ;
// 		}
// 			if(forkmanup(forkes,atoi(argc[1]),2) == 1)
// 				return(0);
// 		free(forkes);
// 		free(dolist);
// 	}
// }
