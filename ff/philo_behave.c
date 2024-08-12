/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:14:51 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/12 15:00:06 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_deed(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead_f);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->is_dead_f);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead_f);
	return (0);
}

void	philo_eating(t_philo *philo)
{
	if (is_deed(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork\n", philo);
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork\n", philo);
	print_message("is eating\n", philo);
	ft_sleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->flag_eat_flag);
	philo->data->flag_eat++;
	pthread_mutex_unlock(&philo->data->flag_eat_flag);
	pthread_mutex_lock(&philo->data->last_meal_f);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_f);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	chb3o(t_philo *philo)
{
	if (philo->data->meals > 0 && philo->meals_eaten >= philo->data->meals)
	{
		pthread_mutex_lock(&philo->data->flag_eat_flag);
		if ((philo->data->meals
				* philo->data->number_philo) == philo->data->flag_eat)
		{
			pthread_mutex_unlock(&philo->data->flag_eat_flag);
			pthread_mutex_lock(&philo->data->all_full_f);
			philo->data->all_full = 1;
			pthread_mutex_unlock(&philo->data->all_full_f);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->flag_eat_flag);
		return (0);
	}
	return (1);
}

int	philo_sleeping(t_philo *philo)
{
	if (is_deed(philo) == 1)
	{
		return (0);
	}
	if (!chb3o(philo))
		return (0);
	print_message("is sleeping\n", philo);
	ft_sleep(philo->data, philo->data->time_to_sleep);
	if (is_deed(philo))
	{
		return (1);
	}
	print_message("is thinking\n", philo);
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
		philo_eating(philo);
		if (!philo_sleeping(philo))
			break ;
		if (philo->data->number_philo < 20)
			usleep(500);
	}
	return (NULL);
}
