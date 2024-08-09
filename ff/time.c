/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:09:12 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/09 19:10:38 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_data *data, long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
        pthread_mutex_lock(&data->is_dead_f);
        if (data->is_dead)
        {
            pthread_mutex_unlock(&data->is_dead_f);
            break;
        }
        pthread_mutex_unlock(&data->is_dead_f);
		usleep(500);
	}
}

int	get_time(void)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	dead_loop(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_ready);
		if (data->ready)
		{
			pthread_mutex_unlock(&data->mutex_ready);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_ready);
	}
}