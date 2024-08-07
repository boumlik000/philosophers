/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:58:17 by mboumlik          #+#    #+#             */
/*   Updated: 2024/08/04 19:06:03 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long get_exacte_time(long start)
{
    return (get_time() - start);
}

ft_sleep(long time)
{
    long start = get_time();
    while(get_time() - start < time);
}

int main()
{
    long start = get_time();
    while(1)
    {
        printf("%ld\n", get_exacte_time(start));
        ft_sleep(100);
        // usleep(100000);
    }
    return 0;
}
