/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:19:53 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/01 11:19:55 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*eat();
static void	*think();
static void	*sleep();

void	*routine()
{
    if (phil_nbr % 2 == 0) // its even
        just alternate
    else if (phil_nbr % 2 != 0) // its odd
        do an algorithm
    if (phil_nbr == 1)
        just die already
}

static void	*eat()
{
    mutex_lock(forks);
    printf("Philosopher %i is eating.\n", i);
    mutex_unlock(forks);
}

static void	*think()
{
    printf("Philosopher %i is thinking.\n", i);
}

static void	*sleep()
{
    get_usleep_time();
    printf("Philosopher %i is sleeping.\n", i);
    usleep();
}
