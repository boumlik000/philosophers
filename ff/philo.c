#include "philo.h"
int malloc_data(t_data *data);

int	get_time()
{
    struct timeval  tv;
    int             time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}
int init_data(t_data *data,int ac,char **av)
{
    
    data->number_philo = atoi(av[1]);
    data->time_to_die = (unsigned long)atoi(av[2]);
    data->time_to_eat = (unsigned long)atoi(av[3]);
    data->time_to_sleep = (unsigned long)atoi(av[4]);
    data->meals = -1;
    if (ac == 6)
        data->meals = atoi(av[5]);

    return malloc_data(data);
}
int malloc_data(t_data *data)
{
    data->philo_struct = malloc(sizeof(t_philo) * data->number_philo);
    if (!data->philo_struct)
        return 2;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);
    if (!data->forks)
        return (free(data->philo_struct),2);
    data->philo_thread = malloc(sizeof(pthread_t) * data->number_philo);
    if (!data->philo_thread)
        return (free(data->philo_struct) , free(data->forks) , 2);
    return 0;
}
void init_forks(t_data *data)
{
    int i = 0;
    while (i < data->number_philo)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
}
int init_philo(t_data *data)
{
    init_forks(data);
    int i = 0;
    while (i < data->number_philo)
    {
        data->philo_struct[i].id = i+1;
        data->philo_struct[i].meals_eaten = 0;
        data->philo_struct[i].right_fork = &data->forks[i];
        data->philo_struct[i].left_fork = &data->forks[(i + 1) % data->number_philo];
        data->philo_struct[i].data = data;
        data->philo_struct[i].last_meal_time = get_time(); 
        // printf("%d\n",(i + 1) % data->number_philo);
        i++;
    }
    return 0;
}
// void *monitor(void *arg)
// {
//     t_data *data = (t_data *)arg;
//     while (1)
//     {
//         for (int i = 0; i < data->number_philo; i++)
//         {
//             int time_since_last_meal = get_time() - data->philo_struct[i].last_meal_time;
//             if (time_since_last_meal > data->time_to_die)
//             {
//                 printf("philo [%d] is dead\n", data->philo_struct[i].id);
//                 exit(0);
//             }
//         }
//         usleep(1000);
//     }
// }
void *philo_behavior(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(100);
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("philo [%d] khda forcheta\n",philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("philo [%d] khda [second] forcheta\n",philo->id);

        printf("\tphilo [%d] is eating\n",philo->id);
        usleep(philo->data->time_to_eat);
        philo->meals_eaten += 1;
        // printf("--%d--\n\n",philo->meals_eaten );
        if(philo->meals_eaten >= philo->data->meals)
        {
            printf("\t\t\tphilo [%d] is full\n",philo->id);
            break;
        }
        
        pthread_mutex_unlock(philo->right_fork);
        printf("philo [%d] 7ett forcheta\n",philo->id);
        pthread_mutex_unlock(philo->left_fork);
        printf("philo [%d] 7ett [second] forcheta\n",philo->id);

        printf("\tphilo [%d] is sleeping\n",philo->id);
        usleep(philo->data->time_to_sleep);

        printf("\tphilo [%d] is thinking\n",philo->id);
        usleep(200000);
    }
    return NULL;
}
void philo(int ac,char **av)
{
    t_data data;
    int i = 0;
    
    if (init_data(&data,ac,av) == 0)
    {
        if (init_philo(&data) != 0)
            printf("error\n"); 
        while (i < data.number_philo)
        {
            pthread_create(&data.philo_thread[i],NULL,philo_behavior, &data.philo_struct[i]);
            i++;
        }
        i = 0;
        while (i < data.number_philo)
        {
            pthread_join(data.philo_thread[i],NULL);
            i++;
        }
    }
    else
        printf("error\n");
    free(data.philo_thread);
    free(data.philo_struct);
    free(data.forks);
}




int main(int ac, char  *av[])
{
    philo(ac,av);
    return 0;
}
