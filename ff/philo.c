/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:07 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/09 19:38:51 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int		malloc_data(t_data *data);
// int		get_time(void);
// void	print_message(char *message, t_philo *philo);

// void	ft_sleep(t_data *data, long time)
// {
// 	long	start;

// 	start = get_time();
// 	while (get_time() - start < time)
// 	{
//         pthread_mutex_lock(&data->is_dead_f);
//         if (data->is_dead)
//         {
//             pthread_mutex_unlock(&data->is_dead_f);
//             break;
//         }
//         pthread_mutex_unlock(&data->is_dead_f);
// 		usleep(500);
// 	}
// }

// int	get_time(void)
// {
// 	struct timeval	tv;
// 	int				time;

// 	gettimeofday(&tv, NULL);
// 	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
// 	return (time);
// }

// int	init_data(t_data *data, int ac, char **av)
// {
// 	data->number_philo = atoi(av[1]);
// 	data->time_to_die = (unsigned long)atoi(av[2]);
// 	data->time_to_eat = (unsigned long)atoi(av[3]);
// 	data->time_to_sleep = (unsigned long)atoi(av[4]);
// 	data->meals = -1;
// 	if (ac == 6)
// 		data->meals = atoi(av[5]);
// 	pthread_mutex_init(&data->general_mutex, NULL);
// 	pthread_mutex_init(&data->print_mutex, NULL);
// 	pthread_mutex_init(&data->mutex_ready, NULL);
// 	pthread_mutex_init(&data->is_dead_f, NULL);
// 	pthread_mutex_init(&data->last_meal_f, NULL);
// 	pthread_mutex_init(&data->flag_eat_flag, NULL);
// 	data->ready = 0;
// 	return (malloc_data(data));
// }
// int	malloc_data(t_data *data)
// {
// 	data->philo_struct = malloc(sizeof(t_philo) * data->number_philo);
// 	if (!data->philo_struct)
// 		return (2);
// 	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);
// 	if (!data->forks)
// 		return (free(data->philo_struct), 2);
// 	data->philo_thread = malloc(sizeof(pthread_t) * data->number_philo);
// 	if (!data->philo_thread)
// 		return (free(data->philo_struct), free(data->forks), 2);
// 	return (0);
// }
// void	init_forks(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->number_philo)
// 	{
// 		pthread_mutex_init(&data->forks[i], NULL);
// 		i++;
// 	}
// }
// int	init_philo(t_data *data)
// {
// 	int	i;

// 	init_forks(data);
// 	i = 0;
// 	while (i < data->number_philo)
// 	{
// 		data->philo_struct[i].id = i + 1;
// 		data->philo_struct[i].meals_eaten = 0;
// 		data->philo_struct[i].right_fork = &data->forks[i];
// 		data->philo_struct[i].left_fork = &data->forks[(i + 1)
// 			% data->number_philo];
// 		data->philo_struct[i].data = data;
// 		data->philo_struct[i].last_meal_time = get_time();
// 		data->flag_eat = 0;
// 		data->all_full = 0;
// 		data->is_dead = 0;
// 		if (data->philo_struct[i].id % 2 == 0)
// 		{
// 			data->philo_struct[i].right_fork = &data->forks[(i + 1)
// 				% data->number_philo];
// 			data->philo_struct[i].left_fork = &data->forks[i];
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	dead_loop(t_data *data)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->mutex_ready);
// 		if (data->ready)
// 		{
// 			pthread_mutex_unlock(&data->mutex_ready);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&data->mutex_ready);
// 	}
// }

// void	*monitor(void *arg)
// {
// 	t_data			*data;
// 	unsigned int	time_since_last_meal;

// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		for (int i = 0; i < data->number_philo; i++)
// 		{
// 			pthread_mutex_lock(&data->last_meal_f);
// 			time_since_last_meal = get_time()
// 				- data->philo_struct[i].last_meal_time;
// 			pthread_mutex_unlock(&data->last_meal_f);
// 			if (time_since_last_meal > data->time_to_die)
// 			{
// 				print_message(BRED"is dead\n"CRESET, &data->philo_struct[i]);
// 				pthread_mutex_lock(&data->is_dead_f);
// 				data->is_dead = 1;
// 				pthread_mutex_unlock(&data->is_dead_f);
// 				return (NULL);
// 			}
// 		}
// 	}
// }

// void	print_message(char *message, t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->print_mutex);
// 	pthread_mutex_lock(&philo->data->all_full_f);
// 	if (philo->data->all_full)
// 	{
// 		pthread_mutex_unlock(&philo->data->print_mutex);
// 		pthread_mutex_unlock(&philo->data->all_full_f);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->data->print_mutex);
// 	pthread_mutex_unlock(&philo->data->all_full_f);
// 	pthread_mutex_lock(&philo->data->print_mutex);
// 	pthread_mutex_lock(&philo->data->is_dead_f);
// 	if (philo->data->is_dead)
// 	{
// 		pthread_mutex_unlock(&philo->data->print_mutex);
// 		pthread_mutex_unlock(&philo->data->is_dead_f);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->data->print_mutex);
// 	pthread_mutex_unlock(&philo->data->is_dead_f);
// 	pthread_mutex_lock(&philo->data->print_mutex);
// 	printf("%ld philo %d %s", get_time() - philo->data->start, philo->id,
// 		message);
// 	pthread_mutex_unlock(&philo->data->print_mutex);
// }

// void	destroy_mutex_data(t_data *data)
// {
// 	int	i;

// 	pthread_mutex_destroy(&data->general_mutex);
// 	pthread_mutex_destroy(&data->print_mutex);
// 	pthread_mutex_destroy(&data->mutex_ready);
// 	pthread_mutex_destroy(&data->is_dead_f);
// 	pthread_mutex_destroy(&data->all_full_f);
// 	pthread_mutex_destroy(&data->flag_eat_flag);
// 	pthread_mutex_destroy(&data->last_meal_f);

// 	i = 0;
// 	while (i < data->number_philo)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		i++;
// 	}
// 	free(data->philo_thread);
// 	free(data->philo_struct);
// 	free(data->forks);
// }

// void	philo_eating(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	print_message(BHCYN"pick up a fork\n"CRESET, philo);
// 	pthread_mutex_lock(philo->right_fork);
// 	print_message(BHCYN"pick up a fork\n"CRESET, philo);
// 	print_message(BHYEL"is eating\n"CRESET, philo);
// 	pthread_mutex_lock(&philo->data->flag_eat_flag);
// 	philo->data->flag_eat++;
// 	pthread_mutex_unlock(&philo->data->flag_eat_flag);
// }

// int	chb3o(t_philo *philo)
// {
// 	if (philo->data->meals > 0 && philo->meals_eaten >= philo->data->meals)
//     {
//         pthread_mutex_lock(&philo->data->general_mutex);
//         if ((philo->data->meals
//                 * philo->data->number_philo) == philo->data->flag_eat)
//         {
//             pthread_mutex_unlock(&philo->data->general_mutex);
//             pthread_mutex_lock(&philo->data->all_full_f);
//             philo->data->all_full = 1;
//             pthread_mutex_unlock(&philo->data->all_full_f);
//             pthread_mutex_unlock(philo->right_fork);
//             pthread_mutex_unlock(philo->left_fork);
//             return (0);
//         }
//         pthread_mutex_unlock(&philo->data->general_mutex);
//         pthread_mutex_unlock(philo->left_fork);
//         pthread_mutex_unlock(philo->right_fork);
// 	    return (0);
//     }
//     return 1;
// }

// int	philo_sleeping(t_philo *philo)
// {
// 	ft_sleep(philo->data, philo->data->time_to_eat);
// 	pthread_mutex_lock(&philo->data->general_mutex);
// 	philo->last_meal_time = get_time();
// 	pthread_mutex_unlock(&philo->data->general_mutex);
// 	philo->meals_eaten += 1;
// 		if (!chb3o(philo))
// 			return (0);
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// 	print_message(BHGRN"is sleeping\n"CRESET, philo);
// 	ft_sleep(philo->data, philo->data->time_to_sleep);
// 	print_message("is thinking\n", philo);
// 	return (1);
// }

// void	*philo_behavior(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0)
// 		usleep(200);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->data->is_dead_f);
// 		if (philo->data->is_dead)
// 		{
// 			pthread_mutex_unlock(&philo->data->is_dead_f);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&philo->data->is_dead_f);
// 		philo_eating(philo);
// 		if(!philo_sleeping(philo))
//             break;
// 	}
// 	return (NULL);
// }

void	create_join(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < data->number_philo)
	{
		pthread_create(&data->philo_thread[i], NULL, philo_behavior,
			&data->philo_struct[i]);
		i++;
	}
	pthread_mutex_lock(&data->mutex_ready);
	data->ready = 1;
	pthread_mutex_unlock(&data->mutex_ready);
	i = 0;
	monitor(data);


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
			printf("error : init philo\n");
			free(data.philo_thread);
			free(data.philo_struct);
			free(data.forks);
		}
		create_join(&data);
	}
	else
	{
		printf("error : init data\n");
		return ;
	}
	destroy_mutex_data(&data);
	return ;
}

int parsing(int ac,char *av[])
{
    if (ac > 6 || ac < 5)
        return 2;
    if (check_data_char(av) != 0)
        return 2;
    if(check_data_atoi(av) != 0)
        return 2;
    return 0;
}
    



int	main(int ac, char *av[])
{
    if (parsing(ac,av) != 0)
    {
        printf("error : parsing\n");
        return 2;
    }
	philo(ac, av);
	return (0);
}
