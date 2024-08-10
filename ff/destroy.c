/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:12:06 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/10 09:14:44 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	destroy_mutex_data(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mutex_ready);
	pthread_mutex_destroy(&data->is_dead_f);
	pthread_mutex_destroy(&data->all_full_f);
	pthread_mutex_destroy(&data->flag_eat_flag);
	pthread_mutex_destroy(&data->last_meal_f);

	i = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philo_thread);
	free(data->philo_struct);
	free(data->forks);
}
