/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:19:10 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 13:19:11 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc > 6 && argc < 5)
	{
		printf("Wrong number of arguments. Try:\n\'");
		printf("./philo\'\n\"Number_of_philosophers\"\n\"Time_to_die");
		printf("\"\n\"Time_to_eat\"\n\"Time_to_sleep\"\n\"Number_of_");
		printf("time_each_philosopher_must_eat\"      *[Optional]*\n");
		return (1);
	}
	if (argv[1] < 1)
		return (printf("Number of Philosophers cant be 0 or less"), 1);
	// init_arguments();
	// phil_loop();
}

/* number of forks = number of phil (argv[1]);
last argument is optional
time to die starts since the beggining of the program, if a philosopher isnt 
eating. time to eat, during this time the philo will hold 2 forks, the left
and the right one. time to sleep after eating? if defined last argument, 
they all need to eat at least this number of times
if they do, simulation stops, if not, simulation stops when a phil die
they sit in a circle, so phil N, sits besides N + 1 and N - 1.
Phil 1 sits next to N - 1 (number of phil) and N + 2 (next) USE A CIRCULAR
Linked list?, each phil must be a thread. so a struct table with structs
phils?*/
