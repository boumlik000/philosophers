/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:07 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/12 10:39:45 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_join(t_data *data)
{
	int			i;
	pthread_t	monitor_th;

	i = 0;
	data->start = get_time();
	while (i < data->number_philo)
	{
		pthread_create(&data->philo_thread[i], NULL, philo_behavior,
			&data->philo_struct[i]);
		i++;
	}
	pthread_create(&monitor_th, NULL, monitor, data);
	i = 0;
	pthread_join(monitor_th, NULL);
	while (i < data->number_philo)
	{
		pthread_join(data->philo_thread[i], NULL);
		i++;
	}
}

void	philo(int ac, char **av)
{
	t_data	data;

	data.ready = 0;
	data.start = get_time();
	if (init_data(&data, ac, av) == 0)
	{
		if (init_philo(&data) != 0)
		{
			ft_printf("error : init philo\n");
			free(data.philo_thread);
			free(data.philo_struct);
			free(data.forks);
		}
		create_join(&data);
	}
	else
	{
		ft_printf("error : init data\n");
		return ;
	}
	destroy_mutex_data(&data);
	return ;
}

int	parsing(int ac, char *av[])
{
	if (ac > 6 || ac < 5)
		return (2);
	if (check_data_char(av) != 0)
		return (2);
	if (check_data_atoi(av) != 0)
		return (2);
	return (0);
}

int	main(int ac, char *av[])
{
	if (parsing(ac, av) != 0)
	{
		ft_printf("error : parsing\n");
		return (2);
	}
	if (ft_atoi(av[1]) == 1)
	{
		single_philo_case(ac, av);
		return (0);
	}
	philo(ac, av);
	return (0);
}
