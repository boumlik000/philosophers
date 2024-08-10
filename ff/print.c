/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:10:15 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/10 09:20:36 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *message, t_philo *philo)
{
	
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->all_full_f);
	if (philo->data->all_full)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->all_full_f);
		return ;
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->all_full_f);
	
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->is_dead_f);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->is_dead_f);
		return ;
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->is_dead_f);
	
	pthread_mutex_lock(&philo->data->print_mutex);
	printf(BHWHT"%ld philo %d %s"CRESET, get_time() - philo->data->start, philo->id,
		message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
