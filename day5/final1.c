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
	int 		forkid;
}				t_fork;

typedef struct to_do
{

	int				numb_philo;
	long int		time_birth;
	long int		time_round;
	long int		time_round_death;
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
	int				*meal_eaten;
    pthread_t		t;
	t_fork			*left;
	t_fork			*right;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *death_lock;
	struct timeval 	m;
	struct timezone y;
}				to_do;

void	print(to_do dolist)
{
	printf("\n_____________________________");
	printf("\nnumb_philo:%d\n", dolist.numb_philo);
	printf("philo_birth_time:%ld\n", dolist.time_birth);
	printf("time_eat: %ld\n", dolist.time_eat);
	printf("time_sleep: %ld\n", dolist.time_sleep);
	printf("time_die: %ld", dolist.time_die);
	printf("\nmeal_plan: %d", *(dolist.meal_eaten));
	printf("\n-----------------------------\n");
}

void mutex_events(to_do *philos, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(&philos->left->fork);
		philos->left->i = 0;
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_lock(&philos->right->fork);
		philos->right->i = 0;
		*(philos->meal_eaten)+=1;
		pthread_mutex_unlock(&philos->right->fork);
	}
	if (flag == 2)
	{
		pthread_mutex_lock(&philos->left->fork);
		philos->left->i = 1;
		pthread_mutex_unlock(&philos->left->fork);
		pthread_mutex_lock(&philos->right->fork);
		philos->right->i = 1;
		pthread_mutex_unlock(&philos->right->fork);
	}
	// if (flag == 3)
	// 		pthread_mutex_lock(print);
	// if (flag == 4)
	// 		pthread_mutex_unlock(print);

}

void threads( to_do *dolist, t_fork *fork, int i)
{
	int count;

	count = -1;
	while (++count<i)
	{
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
		forkes[i].forkid=i+1;
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
int deathchecker (to_do *philo)
{
	int i;

	i = 1;
	// pthread_mutex_lock(philo->death_lock);
	if(*philo->death_event == 1 &&  ((philo->meal_plan > 0 && *philo->meal_eaten == philo->meal_plan )|| philo->meal_plan == 0))
		i = 0;
	// pthread_mutex_unlock(philo->death_lock);
	return (i);
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
	dolist->time_eat = atoi(argc[3]);
	dolist->time_sleep = atoi(argc[4]);
	dolist->time_die = atoi(argc[2]);
	// dolist->time_thinking = dolist->time_die -(dolist->time_eat + dolist->time_sleep);

	// if(dolist->time_thinking < 0)
	dolist->time_thinking = 0;
	if (argc[5])
		dolist->meal_plan = atoi(argc[5])* atoi(argc[1]);
	else
		dolist->meal_plan = 0;
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


void statusprint(to_do *dolist)
{
	// pthread_mutex_lock(dolist->print_mutex);
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
	// pthread_mutex_unlock(dolist->print_mutex);

}

void activity(  to_do * doa, long int *count,long int *limit  )
{
	gettimeofday(&(doa->m), &(doa->y));
		doa->time_round = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000;
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_round);
	 	// if (deathchecker(doa)==0)
		// 		return ;
		statusprint(doa);
		while( *count < *limit)
		{
			gettimeofday(&(doa->m), &(doa->y));
			*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round);
			doa->counttime_die = (doa->m).tv_sec * 1000 + (doa->m).tv_usec/1000  - (doa->time_round_death);
			// if (deathchecker(doa) == 0)
			// 	return ;
			usleep(1);
			pthread_mutex_lock(doa->death_lock);
			if ( deathchecker(doa) == 1 && *(doa->death_event) == 0 && doa->counttime_die == doa->time_die )
			{
					*(doa->death_event) = 1;
				pthread_mutex_unlock(doa->death_lock);
					doa->currentflag = 4;
				pthread_mutex_lock(doa->print_mutex);
					printf("%ld ms: %d is died\n", doa->m.tv_sec * 1000 + doa->m.tv_usec / 1000 - doa->time_birth, doa->numb_philo);
				pthread_mutex_unlock(doa->print_mutex);
				break;
			}

		}
	// if (*(doa->death_event) == 0)
	// 			return ;
	if(doa->currentflag < 3)
		doa->currentflag++;
	else if( doa->currentflag == 3)
		doa->currentflag = 1;
	
	// usleep(5);
}


int eating(to_do *philos)
{
	if((philos->meal_plan) != 0 && *philos->meal_eaten == philos->meal_plan)
		{
			philos->currentflag = 4;
			return 0;
		}
	if(philos->right->i == 1 && philos->left->i == 1)
		{
			gettimeofday(&(philos->m), &(philos->y));
			philos->counttime_die = 0;
			philos->time_round_death = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000;

			// if (deathchecker(philos) == 0)
			// 	return 0;
			mutex_events(philos,1);
				activity(philos, &philos->counttime_eat, &philos->time_eat);
			mutex_events(philos,2);
			return (1);
		}
		return(0);
}

void evenlife (to_do *philos)
{
	if(philos->numb_philo % 2 == 0)
	{
			// printf("\nhi");
		if (deathchecker(philos) == 0)
			return;
		if ( philos->currentflag == 1 && deathchecker(philos) == 1)
			eating(philos);
		else if ( philos->currentflag == 2&& deathchecker(philos) == 1)
			activity(philos, &philos->counttime_sleep, &philos->time_sleep);
		else if ( philos->currentflag == 3&& deathchecker(philos) == 1)
		{
			activity(philos, &philos->counttime_thinking, &philos->time_thinking);
					// philos->currentflag = 1;
		}	
		else if ( philos->currentflag == 4&& deathchecker(philos) == 1)
			return ;
	}
	else
	{
		int i;	
		if (philos->time_die-philos->time_eat > 0)
		 i = philos->time_die-philos->time_eat;
		if (philos->time_die == philos->time_eat)
			i = 0;
		usleep(i);
	} 
}
void oddlife (to_do *philos)
{
	if(philos->numb_philo % 2 > 0)
	{
		if (deathchecker(philos) == 0)
			return;
		if ( philos->currentflag == 1 && deathchecker(philos) == 1)
		{
			eating(philos);
		}
		else if ( philos->currentflag == 2&& deathchecker(philos) == 1)
			activity(philos, &philos->counttime_sleep, &philos->time_sleep);
		else if ( philos->currentflag == 3&& deathchecker(philos) == 1)
		{
			activity(philos, &philos->counttime_thinking, &philos->time_thinking);
					// philos->currentflag = 1;
		}	
		else if ( philos->currentflag == 4&& deathchecker(philos) == 1)
			return ;
	}
	// else
	// {
	// 	int i;
	// 	if (philos->time_die-philos->time_eat > 0)
	// 	 i = philos->time_die-philos->time_eat;
	// 	if (philos->time_die == philos->time_eat)
	// 		i = 0;
	// 	usleep(i);
	// } 
}		

void life( to_do *philos)
{
	if (deathchecker(philos) == 0)
	{
		return;
	}
	evenlife(philos);
	oddlife(philos);
}

void *routine( void *philo_invoid)
{
	to_do philo_rising;
	
	philo_rising = * (to_do *) philo_invoid;
	while (*(philo_rising.death_event)!=2)
	{
		
		if(*(philo_rising.death_event)==1)
			break;
	if((philo_rising.meal_plan) != 0 && *philo_rising.meal_eaten ==philo_rising.meal_plan)
			break;
		life(&philo_rising);
		// usleep(1);
	
	}
	return (void *)0;
}

void starter(to_do *dolist , t_fork *forkes, char *argc[])
{
	pthread_mutex_t printer_lock;
	pthread_mutex_t death_lock;
	struct timeval	m;
	struct timezone	y;
	int i;
	int death;
	int meal;

	death = 0;
	meal = 0;
	i = -1;
	if(pthread_mutex_init(&(printer_lock),NULL) != 0 && pthread_mutex_init(&(death_lock),NULL) != 0)
		return ;
	gettimeofday(&(m), &(y));
	philo_utils_inint( dolist,  forkes,argc, atoi(argc[1]));
	while (++i < atoi(argc[1]) )
	{
		dolist[i].time_birth = m.tv_sec * 1000 + m.tv_usec/1000 ;
		dolist[i].time_round = m.tv_sec * 1000 + m.tv_usec/1000 ;
		dolist[i].time_round_death = m.tv_sec * 1000 + m.tv_usec/1000 ;
		dolist[i].print_mutex = &printer_lock;
		dolist[i].death_lock = &death_lock;
		dolist[i].death_event = &death;
		dolist[i].meal_eaten = &meal;
		if (pthread_create(&(dolist+i)->t,NULL,&routine,((dolist+ i))) != 0)
			return ;
	}
		i = -1;
		while (++i < atoi(argc[1]))
			if (pthread_join((dolist + i)->t,NULL) != 0)
				return ;
}

int main (int argv, char *argc[])
{
	to_do			*dolist;
	t_fork			*forkes;
	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof(to_do)*(atoi(argc[1])));
        forkes = malloc(sizeof(t_fork)*(atoi(argc[1])));
		starter(dolist , forkes,argc);
		// print(*dolist);
			if (forkmanup(forkes,atoi(argc[1]),2) == 1)
				return 1;

		free(forkes);
		free(dolist);
	}
}
