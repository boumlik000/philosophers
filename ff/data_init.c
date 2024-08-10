/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:41 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/10 09:14:38 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	malloc_data(t_data *data)
{
	data->philo_struct = malloc(sizeof(t_philo) * data->number_philo);
	if (!data->philo_struct)
		return (2);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);
	if (!data->forks)
		return (free(data->philo_struct), 2);
	data->philo_thread = malloc(sizeof(pthread_t) * data->number_philo);
	if (!data->philo_thread)
		return (free(data->philo_struct), free(data->forks), 2);
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->number_philo = atoi(av[1]);
	data->time_to_die = (unsigned long)atoi(av[2]);
	data->time_to_eat = (unsigned long)atoi(av[3]);
	data->time_to_sleep = (unsigned long)atoi(av[4]);
	data->meals = -1;
	if (ac == 6)
		data->meals = atoi(av[5]);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->mutex_ready, NULL);
	pthread_mutex_init(&data->is_dead_f, NULL);
	pthread_mutex_init(&data->last_meal_f, NULL);
	pthread_mutex_init(&data->flag_eat_flag, NULL);
	pthread_mutex_init(&data->all_full_f, NULL);
	data->ready = 0;
	return (malloc_data(data));
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_philo(t_data *data)
{
	int	i;

	init_forks(data);
	i = 0;
	while (i < data->number_philo)
	{
		data->philo_struct[i].id = i + 1;
		data->philo_struct[i].meals_eaten = 0;
		data->philo_struct[i].right_fork = &data->forks[i];
		data->philo_struct[i].left_fork = &data->forks[(i + 1)
			% data->number_philo];
		data->philo_struct[i].data = data;
		data->philo_struct[i].last_meal_time = get_time();
		data->flag_eat = 0;
		data->all_full = 0;
		data->is_dead = 0;
		if (data->philo_struct[i].id % 2 == 0)
		{
			data->philo_struct[i].right_fork = &data->forks[(i + 1)
				% data->number_philo];
			data->philo_struct[i].left_fork = &data->forks[i];
		}
		i++;
	}
	return (0);
}
