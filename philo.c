/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:12:40 by mboumlik          #+#    #+#             */
/*   Updated: 2024/07/28 10:40:37 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char  *av[])
{
    if (check_data(ac,av) == 1)
    {
        write(1,"ERROR\n",6);
        return 1;
    }
    if (philosophers(ac,av) != 0)
    {
        return 2;
    }
    return 0;
}



