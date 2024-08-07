#ifndef PHILO_H
#define PHILO_H
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>
#include<stdbool.h>
#include "colors.h"
// #include <string.h>

#define vodi void

typedef struct s_philo
{
    int id;
    int meals_eaten;
    
    struct s_data *data;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int last_meal_time;

}t_philo;

typedef struct s_data
{
    unsigned int time_to_eat;
    unsigned int time_to_die;
    unsigned int time_to_sleep;
    pthread_mutex_t general_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t mutex_ready;

    int flag_eat;
    int meals;
    int check_deth;
    bool ready;
    int number_philo;
    int all_full;
    int is_dead;
    long start;
    t_philo *philo_struct;//allocation
    pthread_t *philo_thread;
    pthread_mutex_t *forks;//allocation
    // int time_since_last_meal;
}t_data;

#endif