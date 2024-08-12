/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:38:42 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/12 10:43:40 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_message("has taken a fork\n", philo);
	ft_sleep(philo->data, philo->data->time_to_die);
	print_message("is dead\n", philo);
	pthread_mutex_lock(&philo->data->is_dead_f);
	philo->data->is_dead = 1;
	pthread_mutex_unlock(&philo->data->is_dead_f);
	return (NULL);
}

void	single_philo_case(int ac, char **av)
{
	t_data		data;
	t_philo		philo;
	pthread_t	thread;

	if (init_data(&data, ac, av) == 0)
	{
		init_philo(&data);
		philo = data.philo_struct[0];
		data.start = get_time();
		pthread_create(&thread, NULL, single_philo, &philo);
		pthread_join(thread, NULL);
		destroy_mutex_data(&data);
	}
	else
	{
		printf("error : init data\n");
	}
}
