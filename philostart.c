/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:01:08 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/02 12:46:18 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int ac, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = (unsigned long)ft_atoi(av[2]);
    data->time_to_eat = (unsigned long)ft_atoi(av[3]);
    data->time_to_sleep = (unsigned long)ft_atoi(av[4]);
    data->meals = -1;
    if (ac == 6)
        data->meals = ft_atoi(av[5]);
    
    pthread_mutex_init(&data->general_mutex,NULL);
    pthread_mutex_init(&data->print_mutex,NULL);
    return (malloc_data(data));
}

int malloc_data(t_data *data)
{
    data->philo = malloc(sizeof(t_philo) * data->nb_philo);
    if (!(data->philo))
        return 2;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!(data->forks))
        return (free(data->philo) ,2);
    data->philotread = malloc(sizeof(pthread_t) * data->nb_philo);
    if (!(data->philotread))
        return (free(data->philo) ,free(data->forks) ,2);
    return 0;
}

void init_forks(t_data *data)
{
    int i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

int init_philos(t_data *data)
{
    int i = 0;
    init_forks(data);
    while (i < data->nb_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].meal_eated = 0;
        data->philo[i].fork_right = &data->forks[i];
        data->philo[i].fork_left = &data->forks[(i + 1) % data->nb_philo];
        i++; 
    }
    return 0;
}
void *philosopher_behavior(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    // philo->data->last_meal_time = (unsigned long)get_time();
    // philo->data->meals_count = 0;
    while (1)
    {
        printf(" philo [%d] is thinking.\n",philo->id);
        usleep(200000);

        // Eating
        if (philo->id % 2 == 0)
            usleep(100);
        pthread_mutex_lock(philo->fork_left);  // Pick up left fork
        printf("Philosopher [%d] khda forchita.\n", philo->id);
        pthread_mutex_lock(philo->fork_right); // Pick up right fork
        printf("Philosopher [%d] khda forchita.\n", philo->id);
        printf("Philosopher [%d] is eating.\n", philo->id);
        
        usleep(philo->data->time_to_eat);  // Eat for a random amount of time
        
        pthread_mutex_unlock(philo->fork_right); // Put down right fork
        printf("Philosopher [%d] 7ett forchita.\n", philo->id);
        pthread_mutex_unlock(philo->fork_left);  // Put down left fork
        printf("Philosopher [%d] 7ett forchita.\n", philo->id);
        
        // if (get_time() - philo->data->last_meal_time > philo->data->time_to_die) {
        //     printf("Philosopher [%d]has died.\n", philo->id);
        //     break;
        // }

        // // Check if philosopher has eaten enough meals
        // if (philo->data->last_meal_time >= philo->data->meals) {
        //     printf("Philosopher [%d] has eaten enough meals.\n", philo->id);
        //     break;
        // }
        // philo->data->last_meal_time = get_time();
        // philo->data->meals_count++;
    }
    return NULL;
}
int philosophers(int ac,char **av)
{
    t_data data;
    if (init_data(&data,ac,av) != 0)
        return 2;
    if (init_philos(&data))
        return 3;
    int i = 0;
    while (i < data.nb_philo) {
        pthread_create(&data.philotread[i], NULL, philosopher_behavior, &data.philo[i]);
        i++;
    }
    
    // Wait for all data->philotread to finish
    int j = 0;
    while (j < data.nb_philo) {
        pthread_join(data.philotread[j], NULL);
        j++;
    }

    free(data.philotread);
    return 0;
}