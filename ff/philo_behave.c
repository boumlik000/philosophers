/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:14:51 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/10 09:50:03 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(BHCYN"has taken a fork\n"CRESET, philo);
	pthread_mutex_lock(philo->right_fork);
	print_message(BHCYN"has taken a fork\n"CRESET, philo);
	print_message(BHYEL"is eating\n"CRESET, philo);
	ft_sleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->flag_eat_flag);
	philo->data->flag_eat++;
	pthread_mutex_unlock(&philo->data->flag_eat_flag);
}

int	chb3o(t_philo *philo)
{
	if (philo->data->meals > 0 && philo->meals_eaten >= philo->data->meals)
    {
        pthread_mutex_lock(&philo->data->all_full_f);
        if ((philo->data->meals
                * philo->data->number_philo) == philo->data->flag_eat)
        {
            pthread_mutex_unlock(&philo->data->all_full_f);
            pthread_mutex_lock(&philo->data->all_full_f);
            philo->data->all_full = 1;
            pthread_mutex_unlock(&philo->data->all_full_f);
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (0);
        }
        pthread_mutex_unlock(&philo->data->all_full_f);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
	    return (0);
    }
    return 1;
}

int	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_meal_f);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_f);
	philo->meals_eaten += 1;
		if (!chb3o(philo))
			return (0);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_sleep(philo->data, philo->data->time_to_sleep);
	print_message(BHGRN"is sleeping\n"CRESET, philo);
	print_message(BHWHT"is thinking\n"CRESET, philo);
	return (1);
}

void	*philo_behavior(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->data->is_dead_f);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->is_dead_f);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->is_dead_f);
		philo_eating(philo);
		if(!philo_sleeping(philo))
            break;
	}
	return (NULL);
}
