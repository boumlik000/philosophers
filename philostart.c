/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:01:08 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/28 11:19:02 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data,int ac,char **av)
{
    data->nb_all_philo = 0;
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = (unsigned long)ft_atoi(av[2]);
    data->time_to_eat = (unsigned long)ft_atoi(av[3]);
    data->time_to_sleep = (unsigned long)ft_atoi(av[4]);
    data->meals = -1;
    if (ac == 6)
        data->meals = ft_atoi(av[5]);
    
}

int philosophers(int ac,char **av)
{
    t_data *data;
    if (init_data(&data,ac,av) == 1)
    {
        return 2;
    }
    
}