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

static void	cleanup(t_philo *philos, t_fork *fork);
static void	init(t_philo *philos, t_fork *fork, int n);

int	main(int argc, char **argv)
{
	t_philo	philos[ft_atoi(argv[1])];
	t_fork	fork[ft_atoi(argv[1])];

	if (parsing(argv, argc) != 0)
		return (1);
	init(philos, fork, argv[1]);
	cleanup(philos, fork);
	return (0);
}

static int	init(t_philo *philos, t_fork *fork, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&fork, NULL) != 0)
			return (printf("Error: mutex_init\n"), 1);
	i = -1;
	while (++i < n)
		if (pthread_create(philos[i], NULL, &monitor, NULL) != 0)
			return (printf("Error: thread create.\n"), 1);
	i = -1;
	while (philos[++i])
		if (pthread_join(philos[i], NULL) != 0)
			return (printf("Error: thread join.\n"), 1);
}

static void	cleanup(t_philo *philos, t_fork *fork)
{
	pthread_mutex_destroy(&fork);
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
