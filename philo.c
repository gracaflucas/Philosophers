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

static void	cleanup(t_table *table);
static int	init(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;

	if (parsing(&table, argv, argc) == 0)
	{
		init(&table);
		cleanup(&table);
	}
	return (0);
}

static int	init(t_table *table)
{
	table->end = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (printf("Error: Memory allocation.\n"), 1);

	/*int	i;

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
			return (printf("Error: thread join.\n"), 1);*/
	return (0);
}

static void	cleanup(t_table *table)
{
	pthread_mutex_destroy(table->forks);
	free (table->philos);
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
