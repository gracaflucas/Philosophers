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

static int	argument_error()
{
	printf("Wrong number of arguments. Try:\n\'");
	printf("./philo\'\n\"Number_of_philosophers\"\n\"Time_to_die");
	printf("\"\n\"Time_to_eat\"\n\"Time_to_sleep\"\n\"Number_of_");
	printf("time_each_philosopher_must_eat\"      *[Optional]*\n");
	return (1);
}

static long	ft_atol(const char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
		return (printf("Error: negative number.\n"), 1);
	if (nptr[i] < '0' || nptr[i] > '9')
		return (printf("Error: Argument isnt a number.\n"), 1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (result > INT_MAX)
		return (printf("Error: INT_MAX.\n"), 1);
	return (result);
}

int	parsing(t_table *table, char **argv, int argc)
{
	if (argc > 6 || argc < 5)
		return (argument_error(), 1);
	table->philo_nbr = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]) * 1000;
	table->time_eat = ft_atol(argv[3]) * 1000;
	table->time_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_eat < 60000 || table->time_sleep < 60000
			|| table->time_die < 60000)
		return (printf("Error: Time not greater than  60ms.\n"), 1);
	if (table->philo_nbr < 1)
		return (printf("Error: Number of Philosophers can't be 0 or less.\n"), 1);
	if (argv[5])
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	return (0);
}

int	init(t_table *table)
{
	int	i;

	table->end = 0; // fim da simulacao = end == 1;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (printf("Error: Memory allocation.\n"), 1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (printf("Error: Memory allocation.\n"), 1);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (printf("Error: mutex_init\n"), 1);
		table->forks[i].id = i;
	}
	init_philo(&table);
	return (0);
}
// if odd philo, pick left first
// if even philo, pick right first
static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos.id = i + 1; // conta a partir do 1; pra garantir se é par ou impar
		table->philos.meals = 0;
		table->philos.full = 0; // se chegar ao max meals, para de comer e espera acabar a simulacao
		if (i % 2 == 0)
		{
			table->philos.right = &table->forks[table->philos.id - 1];
			table->philos.left = &table->forks[table->philos.id % table->philo_nbr];
		}
		else if (i % 2 != 0)
		{
			table->philos.left = &table->forks[table->philos.id % table->philo_nbr];
			table->philos.right = &table->forks[table->philos.id - 1];
		}
	}
}