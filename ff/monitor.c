/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:16:47 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/10 09:52:02 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data			*data;
	unsigned int	time_since_last_meal;

	data = (t_data *)arg;
	while (1)
	{
		int i = 0;
		while (i < data->number_philo)
		{
			pthread_mutex_lock(&data->last_meal_f);
			time_since_last_meal = get_time()
				- data->philo_struct[i].last_meal_time;
			pthread_mutex_unlock(&data->last_meal_f);
			if (time_since_last_meal > data->time_to_die)
			{
				print_message(BRED"died\n"CRESET, &data->philo_struct[i]);
				pthread_mutex_lock(&data->is_dead_f);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->is_dead_f);
				return (NULL);
			}
			i++;
			usleep(1000);
		}
	}
}
