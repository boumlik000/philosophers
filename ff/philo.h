/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:16:00 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/12 10:41:24 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;

	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		monitor_;

	int				last_meal_time;

}					t_philo;

typedef struct s_data
{
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mutex_ready;
	pthread_mutex_t	is_dead_f;
	pthread_mutex_t	all_full_f;
	pthread_mutex_t	last_meal_f;
	pthread_mutex_t	flag_eat_flag;

	int				flag_eat;
	int				meals;
	int				check_deth;
	bool			ready;
	int				number_philo;
	int				all_full;
	int				is_dead;
	long			start;

	t_philo			*philo_struct;
	pthread_t		*philo_thread;
	pthread_mutex_t	*forks;
}					t_data;

int					check_data_atoi(char **av);
int					check_data_char(char **av);
int					ft_atoi(char *str);
int					is_deed(t_philo *philo);
int					init_philo(t_data *data);
void				init_forks(t_data *data);
int					init_data(t_data *data, int ac, char **av);
int					malloc_data(t_data *data);
void				ft_sleep(t_data *data, long time);
int					get_time(void);
void				dead_loop(t_data *data);
void				print_message(char *message, t_philo *philo);
void				destroy_mutex_data(t_data *data);
void				philo_eating(t_philo *philo);
int					chb3o(t_philo *philo);
int					philo_sleeping(t_philo *philo);
void				*philo_behavior(void *arg);
void				*monitor(void *arg);
void				single_philo_case(int ac, char **av);
void				*single_philo(void *arg);

#endif