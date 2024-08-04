/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:16:56 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/01 21:22:59 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct s_philo
{   
    int id;
    int die;
    int meal_eated;
    struct s_data *data;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
} t_philo;

typedef struct s_data
{
    int nb_philo;
    // int nb_all_philo;
    unsigned long time_to_die;
    unsigned long time_to_eat;
    unsigned long time_to_sleep;
    unsigned long meals;
    int meals_count;
    int philo_die;
    unsigned long last_meal_time;
    pthread_mutex_t print_mutex;
    pthread_mutex_t general_mutex;
    // pthread_mutex_t print_mutex;

    pthread_t *philotread;
    pthread_mutex_t *forks;
    t_philo *philo;
}t_data;

//utils
int ft_atoi(char *str);
int check_data(int ac,char **av);

//parsing
int check_data_atoi(char **av);
int check_data_char(char **av);
int check_data(int ac,char **av);

//mandatory
int init_data(t_data *data,int ac,char **av);
int philosophers(int ac,char **av);

int malloc_data(t_data *data);
void init_forks(t_data *data);
int init_philos(t_data *data);
void *philosopher_behavior(void *arg);
int philosophers(int ac,char **av);

#endif 
