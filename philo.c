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

static void	cleanup(pthread_t *philos, pthread_mutex_t mutex);
static void	init(pthread_t *philos, pthread_mutex_t mutex, int n);

int	main(int argc, char **argv)
{
	pthread_t		philos[ft_atoi(argv[1])];
	pthread_mutex_t	mutex;

	if (argc > 6 && argc < 5)
		return (argument_error(), 1);
	if (ft_atoi(argv[1]) < 1)
		return (printf("Number of Philosophers can't be 0 or less"), 1);
	init(philos, mutex, argv[1]);
	// phil_loop();
	cleanup(philos, mutex);
	return (0);
}

static int	init(pthread_t *philos, pthread_mutex_t mutex, int n)
{
	int	i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < n)
	{
		if (pthread_create(philos[i], NULL, &monitor, NULL) != 0)
			return (printf("Error creating thread. %i\n", i), 1);
		i++;
	}
	i = 0;
	while (philos[i])
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (printf("Error joining thread.\n"), 1);
		i++;
	}
}

static void	cleanup(pthread_t *philos, pthread_mutex_t mutex)
{
	pthread_mutex_destroy(&mutex);
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
phils?
use a monitor to get info in between the philosophers
when eating, get time of last meal, so to do a priority in what phil must eat
the monitor checks the availability of forks and the priority list
do a function for each routine, so a function for eating, one for sleeping and one for thinking
distinguish philosophers between odd and even? i % 2 = 0
*/
