#include "Philosphers.h"

void inint_fork_placement( to_do *dolist, t_fork *fork, int i)
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
		forkes[i].i = 1;
		forkes[i].forkid = i + 1;
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
void	setdolist(to_do *dolist, char *argc[], int i)
{
	dolist->numb_philo = i+1;
	dolist->time_eat = atoi(argc[3]);
	dolist->time_sleep = atoi(argc[4]);
	dolist->time_die = atoi(argc[2]);
	dolist->time_thinking = 0;
	if (argc[5])
		dolist->meal_plan = atoi(argc[5])* atoi(argc[1]);
	else
		dolist->meal_plan = 0;
}

void philo_utils_inint(to_do dolist[], t_fork *forkes, char* argc[],int length)
{
	int i;
	pthread_mutex_t printer_lock;
	pthread_mutex_t death_lock;
	pthread_mutex_t eat_lock;
    int             death;

    death = 0;	
	i = -1;
    if(pthread_mutex_init(&(printer_lock),NULL) != 0 )
            return ;
	if (pthread_mutex_init(&(death_lock),NULL) != 0 )
            return ;
	if (pthread_mutex_init(&(eat_lock),NULL) != 0)
            return ;
	inint_fork_placement(dolist,forkes,length);
	while (++i < length)
	{
			dolist[i].currentflag = 1;
            dolist[i].print_mutex = &printer_lock;
		    dolist[i].death_lock = &death_lock;
		    dolist[i].eat_lock = &eat_lock;
			setdolist(&(dolist[i]), argc, i);
	}
	starter(dolist ,argc , death);
	if(pthread_mutex_destroy(&(printer_lock)) != 0 )
            return ;
	if (pthread_mutex_destroy(&(death_lock)) != 0 )
            return ;
	if (pthread_mutex_destroy(&(eat_lock)) != 0)
            return ;
}
