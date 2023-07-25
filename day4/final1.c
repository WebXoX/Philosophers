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
void threads( to_do *dolist, t_fork *fork, int i)
{
	int count;

	count = -1;
	while (++count<i)
	{
		if(count + 1  == i)
			(dolist + count)->right = (fork);
		else
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
	pthread_mutex_lock(dolist->print_mutex);
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
	pthread_mutex_unlock(dolist->print_mutex);

}

void activity(  to_do * doa, long int *count,long int *limit  )
{
	gettimeofday(&(doa->m), &(doa->y));
	
		*count = (doa->m).tv_sec * 1000 + (doa->m).tv_usec / 1000  - (doa->time_birth);
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
	
	// usleep(5);
}

int deathchecker (to_do *philo)
{
	int i;

	i = 1;
	pthread_mutex_lock(philo->death_lock);
	if(*philo->death_event == 1)
		i = 0;
	pthread_mutex_unlock(philo->death_lock);
	return (i);
}
int eating(to_do *philos)
{
	if(philos->right->i == 1 && philos->left->i == 1)
		{
			gettimeofday(&(philos->m), &(philos->y));
			philos->counttime_die = 0;
			philos->counttime_die = (philos->m).tv_sec * 1000 + (philos->m).tv_usec/1000  - (philos->time_round);

			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,1);
				philos->right->i--;
				philos->left->i--; 
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
				activity(philos, &philos->counttime_eat, &philos->time_eat);
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,1);
				philos->right->i++;
				philos->left->i++;
			mutex_events(&philos->left->fork,&philos->right->fork,philos->print_mutex,2);
			return (1);
		}
		return(0);
}
void life( to_do *philos)
{
	pthread_mutex_lock(philos->death_lock);
	if (*philos->death_event == 1)
{
pthread_mutex_lock(philos->death_lock);
	return;
}	

	if ( philos->currentflag == 1 && *philos->death_event == 0)
	{
		// pthread_mutex_unlock(philos->death_lock);
			// printf("hi from eating\n");
		printf("philo num: %d eating\n",philos->numb_philo); 

		philos->currentflag++;
	}
	else if ( philos->currentflag == 2&& *philos->death_event == 0)

{
			// pthread_mutex_unlock(philos->death_lock);

			printf("hi from sleeping\n");
philos->currentflag++; 
}
	else if ( philos->currentflag == 3&& *philos->death_event == 0)
	{
			// pthread_mutex_lock(philos->death_lock);
			printf("hi from thinking\n");
	philos->currentflag++;
	}
	else if ( philos->currentflag == 4&& *philos->death_event == 0)

			{
			// pthread_mutex_unlock(philos->death_lock);

			printf("hi from dying \n");
			philos->currentflag++;
			pthread_mutex_lock(philos->death_lock);
			if (*philos->death_event == 0)
			{
				*philos->death_event =1;
				printf("philo num: %d dead\n",philos->numb_philo); 
			pthread_mutex_unlock(philos->death_lock);
			}
			}

}

void *routine( void *philo_invoid)
{
	to_do philo_rising;
	
	philo_rising = * (to_do *) philo_invoid;
	while (deathchecker(&philo_rising))
	{
		
		// if(*(philo_rising.death_event)==1)
		// 	break;

		life(&philo_rising);
		// break;
	
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

	death = 0;
	i = -1;
	if(pthread_mutex_init(&(printer_lock),NULL) != 0 && pthread_mutex_init(&(death_lock),NULL) != 0)
		return ;
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
				return ;
		}
		i = -1;
		while (++i < atoi(argc[1]))
			if (pthread_join((dolist + i)->t,NULL) != 0)
				return ;
		if (forkmanup(forkes,atoi(argc[1]),2) == 1)
			return ;
}


int main (int argv, char *argc[])
{
	to_do			*dolist;
	t_fork			*forkes;
	pthread_mutex_t printer_lock;
	pthread_mutex_t death_lock;

	int i;

	if ((argv == 5 || argv == 6) && checker(argc) == 1)
	{
        dolist = malloc(sizeof(to_do)*(atoi(argc[1])));
        forkes = malloc(sizeof(t_fork)*(atoi(argc[1])));
		starter(dolist , forkes,argc);
		free(forkes);
		free(dolist);
	}
}