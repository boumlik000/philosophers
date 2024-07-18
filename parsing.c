/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:36:16 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/18 20:29:32 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parsing(int ac ,char **av)
{
    if (ac == 6)
    {
        int num_p ;
        int  time_d;
        int time_e;
        int time_s;
        int num_p_e;
        
        int i = 1;
        while (av[i])
        {
            if (isnumber(av[i]) == 0)
            {
                printf("Error not number\n");
                exit(1);
            }
            i++;
        }
        num_p = ft_atoi(av[1]);
        time_d = ft_atoi(av[2]);
        time_e = ft_atoi(av[3]);
        time_s = ft_atoi(av[4]);
        num_p_e = ft_atoi(av[5]);
        if (num_p <= 0 || time_d <= 0
            || time_e <=0 || time_s <= 0 || num_p_e <= 0)
        {
            printf("ERROR\n");
            exit(1);
        }
    }
    return 0;
}
