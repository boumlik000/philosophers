/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:00:48 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/18 20:29:06 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int isnumber(char *str) {
    int i = 0;
    if (str[i] == '-' || str[i] == '+') {
        str++; // skip the sign
    }
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9') {
            return 0; // Not a digit
        }
        i++;
    }
    return 1;
}

int ft_atoi(char *str)
{
    int (i),(j),(sign);

    i = 0;
    j  = 0;
    sign = 1;
    while (str[i] >= 9 && str[i] <= 13)
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        j = j*10 + str[i] -'0';
        i++;
    }
    return j*sign;
}