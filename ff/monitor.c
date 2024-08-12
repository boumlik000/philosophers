/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:16:47 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/12 15:11:25 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define RED "\e[1;31m"
#define RESET "\e[0m"

void	lockk(t_data *data)
{
	pthread_mutex_lock(&data->is_dead_f);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->is_dead_f);
}



static void *monitor_part2(t_data *data, int i, unsigned int time_since_last_meal)
{
    pthread_mutex_lock(&data->all_full_f);
    if (data->all_full)
    {
        pthread_mutex_unlock(&data->all_full_f);
        return NULL;
    }
    pthread_mutex_unlock(&data->all_full_f);
    if (time_since_last_meal > data->time_to_die)
    {
        lockk(data);
        printf(RED "%ld %d died\n" RESET, get_time() - data->start,
            data->philo_struct[i].id);
        return NULL;
    }
    return (void *)1;
}

void *monitor(void *arg)
{
    t_data *data;
    unsigned int time_since_last_meal;
    int i;
    void *result;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while (i < data->number_philo)
        {
            pthread_mutex_lock(&data->last_meal_f);
            time_since_last_meal = get_time()
                - data->philo_struct[i].last_meal_time;
            pthread_mutex_unlock(&data->last_meal_f);
            result = monitor_part2(data, i, time_since_last_meal);
            if (result != (void *)1)
                return result;
            i++;
            usleep(1000);
        }
    }
}
// void	*monitor(void *arg)
// {
// 	t_data			*data;
// 	unsigned int	time_since_last_meal = 0;;
// 	int				i;

// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->number_philo)
// 		{
// 			pthread_mutex_lock(&data->last_meal_f);
// 			time_since_last_meal = get_time()
// 				- data->philo_struct[i].last_meal_time;
// 			pthread_mutex_unlock(&data->last_meal_f);
// 			pthread_mutex_lock(&data->all_full_f);
// 			if (data->all_full)
// 			{
// 				pthread_mutex_unlock(&data->all_full_f);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->all_full_f);
// 			if (time_since_last_meal > data->time_to_die)
// 			{
// 				lockk(data);
// 				printf(RED "%ld %d died\n" RESET, get_time() - data->start,
// 					data->philo_struct[i].id);
// 				return (NULL);
// 			}
// 			// lock_full(data,i,time_since_last_meal);
// 			i++;
// 			usleep(1000);
// 		}
// 	}
// }
