/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:36:34 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 13:36:44 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    argument_error()
{
    printf("Wrong number of arguments. Try:\n\'");
	printf("./philo\'\n\"Number_of_philosophers\"\n\"Time_to_die");
	printf("\"\n\"Time_to_eat\"\n\"Time_to_sleep\"\n\"Number_of_");
	printf("time_each_philosopher_must_eat\"      *[Optional]*\n");
    return (1);
}