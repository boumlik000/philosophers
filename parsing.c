/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:36:16 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/28 10:29:47 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_data_atoi(char **av)
{
    int i = 1;
    while (av[i])
    {
        if (ft_atoi(av[i]) <= 0)
            return 1;
        i++;
    }
    return 0;
}

int check_data_char(char **av)
{
    int i = 1;
    int j = 0;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] == '-' || av[i][j] == '+')
                j++;
            if (av[i][j] < '0' || av[i][j] > '9')
                return 1;
            j++;
        }   
        i++;
    }
    return 0;
}

int check_data(int ac,char **av)
{
    if (ac > 6 || ac < 5)
        return 1;
    if (check_data_char(av) != 0)
        return 1;
    if(check_data_atoi(av) != 0)
        return 1;
    return 0;
}
