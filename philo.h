/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:16:56 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/28 11:50:34 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_data{
    int nb_philo;
    int nb_all_philo;
    unsigned long time_to_die;
    unsigned long time_to_eat;
    unsigned long time_to_sleep;
    int meals;

    t_philo *philo;
        
}t_data;
typedef struct s_philo
{
    int id;
    t_data *data;
}t_philo;

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

#endif 
