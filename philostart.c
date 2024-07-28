/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:01:08 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/28 17:29:20 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data,int ac,char **av)
{
    data->nb_all_philo = 0;
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = (unsigned long)ft_atoi(av[2]);
    data->time_to_eat = (unsigned long)ft_atoi(av[3]);
    data->time_to_sleep = (unsigned long)ft_atoi(av[4]);
    data->meals = -1;
    if (ac == 6)
        data->meals = ft_atoi(av[5]);
    pthread_mutex_init(&data->time_to_eat,NULL);
    pthread_mutex_init(&data->time_to_sleep,NULL);
    pthread_mutex_init(&data->time_to_die,NULL);
    pthread_mutex_init(&data->nb_philo,NULL);
    return malloc_data(data);
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
int philosophers(int ac,char **av)
{
    t_data *data;
    if (init_data(&data,ac,av) != 0)
        return 2;
    
}