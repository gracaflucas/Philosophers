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

int	argument_error()
{
	printf("Wrong number of arguments. Try:\n\'");
	printf("./philo\'\n\"Number_of_philosophers\"\n\"Time_to_die");
	printf("\"\n\"Time_to_eat\"\n\"Time_to_sleep\"\n\"Number_of_");
	printf("time_each_philosopher_must_eat\"      *[Optional]*\n");
	return (1);
}

int	parsing(char **argv, int argc)
{
	int	i;
	int	j;

	i = -1;
	if (argc > 6 && argc < 5)
		return (argument_error(), 1);
	if (ft_atoi(argv[1]) < 1) // need to do this for all arguments, to check if its positive
		return (printf("Error: Number of Philosophers can't be 0 or less"), 1);
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] > '9' && argv[i][j] < '0')
				return (printf("Error: Wrong Arguments.\n"), 1);
		if (ft_atoi(argv[i]) > INT_MAX)
			return (printf("Error: INT_MAX"), 1);
	}
	return (0);
}
