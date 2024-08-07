#include "philo.h"
int malloc_data(t_data *data);
int	get_time();
void print_message(char *message, t_philo *philo);
void ft_sleep(long time)
{
    long start = get_time();
    while(get_time() - start < time);
}

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
    pthread_mutex_init(&data->general_mutex, NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->mutex_ready, NULL);
    data->ready = 0;
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
        data->flag_eat = 0; 
        data->all_full = 0; 
        data->is_dead = 0; 
        if(data->philo_struct[i].id % 2 == 0)
        {
            data->philo_struct[i].right_fork =&data->forks[(i + 1) % data->number_philo];
            data->philo_struct[i].left_fork = &data->forks[i];
        }
        i++;
    }
    return 0;
}

vodi dead_loop(t_data *data)
{
    int ready = 0;
    while (!ready)
    {
        pthread_mutex_lock(&data->mutex_ready);
        ready = data->ready;
        pthread_mutex_unlock(&data->mutex_ready);
        if (!ready)
            usleep(1000);  // Short sleep to avoid busy-waiting
    }
}

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    dead_loop(data);
    while (1)
    {
        for (int i = 0; i < data->number_philo; i++)
        {
            pthread_mutex_lock(&data->general_mutex);
            unsigned int time_since_last_meal = get_time() - data->philo_struct[i].last_meal_time;
            pthread_mutex_unlock(&data->general_mutex);

            if (time_since_last_meal > data->time_to_die)
            {
                print_message("is dead++++++++++++++++++++++\n",data->philo_struct);
                pthread_mutex_lock(&data->general_mutex);
                data->is_dead = 1; 
                pthread_mutex_unlock(&data->general_mutex);
                return (NULL);
            }
        }
    }
}


void print_message(char *message, t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->general_mutex);
    if (philo->data->all_full)
    {
        pthread_mutex_unlock(&philo->data->general_mutex);
        pthread_mutex_unlock(&philo->data->print_mutex);
        return ;
    }
    if (philo->data->is_dead)
    {
        pthread_mutex_unlock(&philo->data->general_mutex);
        pthread_mutex_unlock(&philo->data->print_mutex);
        return ;
    }
    
    pthread_mutex_unlock(&philo->data->print_mutex);
    pthread_mutex_unlock(&philo->data->general_mutex);
    
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld philo %d %s", get_time() - philo->data->start, philo->id, message);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
void printn(char *message, t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->general_mutex);
    if (philo->data->all_full)
    {
        pthread_mutex_unlock(&philo->data->general_mutex);
        printf("%s\n",message);
        pthread_mutex_unlock(&philo->data->print_mutex);
        return ;
    }
    pthread_mutex_unlock(&philo->data->general_mutex);
    pthread_mutex_unlock(&philo->data->print_mutex);
    return ;
}
void destroy_mutex_data(t_data *data)
{
    pthread_mutex_destroy(&data->general_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->mutex_ready);
    int  i = 0;
    while (i < data->number_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
}
void *philo_behavior(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(250);
    dead_loop(philo->data);
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_message("pick up a fork\n", philo);
        pthread_mutex_lock(philo->right_fork);
        print_message("pick up a second fork\n", philo);

        print_message("is eating\n", philo);
        pthread_mutex_lock(&philo->data->general_mutex);
        philo->data->flag_eat++;
        pthread_mutex_unlock(&philo->data->general_mutex);
        ft_sleep(philo->data->time_to_eat);

        pthread_mutex_lock(&philo->data->general_mutex);
        philo->last_meal_time = get_time();
        pthread_mutex_unlock(&philo->data->general_mutex);
        philo->meals_eaten += 1;
        if(philo->data->meals > 0 && philo->meals_eaten >= philo->data->meals)
        {
            pthread_mutex_lock(&philo->data->general_mutex);
            if ((philo->data->meals * philo->data->number_philo) == philo->data->flag_eat)
            {
                pthread_mutex_unlock(&philo->data->general_mutex);
                pthread_mutex_lock(&philo->data->general_mutex);
                philo->data->all_full = 1; 
                pthread_mutex_unlock(&philo->data->general_mutex);
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(philo->left_fork);
                return 0;
            }
            pthread_mutex_unlock(&philo->data->general_mutex);
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            break;
        }
        
        pthread_mutex_unlock(philo->left_fork);
        print_message("take off second fork\n",philo);

        pthread_mutex_unlock(philo->right_fork);
        print_message("take off fork\n",philo);

        print_message("is sleeping\n",philo);
        ft_sleep(philo->data->time_to_sleep);

        print_message("is thinking\n",philo);
    }
    return NULL;
}
void philo(int ac,char **av)
{
    t_data data;
    int i = 0;
    pthread_t monitor_;
    data.ready = 0;
    data.start = get_time();
    if (init_data(&data,ac,av) == 0)
    {
        if (init_philo(&data) != 0)
        {
            printf("error\n"); 
            // destroy_mutex_data(&data);
            free(data.philo_thread);
            free(data.philo_struct);
            free(data.forks);
        }
        while (i < data.number_philo)
        {
            pthread_create(&data.philo_thread[i],NULL,philo_behavior, &data.philo_struct[i]);
            i++;
        }
        pthread_create(&monitor_,NULL,monitor, &data);
        pthread_mutex_lock(&data.mutex_ready);
        data.ready = 1;
        pthread_mutex_unlock(&data.mutex_ready);
        i = 0;
        while (i < data.number_philo)
        {
            pthread_join(data.philo_thread[i],NULL);
            i++;
        }
        pthread_join(monitor_,NULL);
    }
    else
    {
        printf("error\n");
        return;
    }
    destroy_mutex_data(&data);
    free(data.philo_thread);
    free(data.philo_struct);
    free(data.forks);
    return ;
}


int main(int ac, char  *av[])
{
    philo(ac,av);
    return 0;
}
