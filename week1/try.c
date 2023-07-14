#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>

typedef struct to_do
{
    int numb_philo;
    int time_eat;
    int time_sleep;
    int time_die;
    int meal_plan;
}       to_do;
typedef struct t_time
{
    timeval current_time;
    timezone zone;
}       t_time;

int checker(char *ptr[])
{
    int i;
    int j;

    i = 0;
    while ((ptr[++i]))
    {
        j = -1;
        while(ptr[i][++j])
            if(!((ptr[i][j])>='0' && (ptr[i][j])<='9'))
                return (0);
    }
    return (1);
}
void setdolist(to_do *dolist, char *argc[])
{
    dolist->numb_philo = atoi(argc[1]);
    dolist->time_eat = atoi(argc[2]);
    dolist->time_sleep = atoi(argc[3]);
    dolist->time_die = atoi(argc[4]);
    if(argc[5])
        dolist->meal_plan = atoi(argc[5]);
    else
        dolist->meal_plan = 0;

}
void print(to_do *dolist)
{
    printf("\n_____________________________");
    printf("\nnumb_philo:%d\n",dolist->numb_philo);
    printf("time_eat: %d\n",dolist->time_eat);
    printf("time_sleep: %d\n",dolist->time_sleep);
    printf("time_die: %d",dolist->time_die);
    printf("\nmeal_plan: %d",dolist->meal_plan);
    printf("\n-----------------------------\n");
}
int main(int argv, char *argc[])
{
    to_do dolist;
    t_time mtime;

    if ((argv == 5 || argv == 6) && checker(argc)==1)
        setdolist(&dolist, argc);
        print(&dolist);
        prinf("%d",gettimeofday(&mtime.current_time,&mtime.zone));
}
