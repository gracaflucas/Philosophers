/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:55:52 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/26 10:55:53 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_end(t_table *table);
static void	check_dead(t_philo *philo);

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;
	int		full;

	table = (t_table *)arg;
	while (1)
	{
		if (check_end(table) == 1)
			return (NULL);
		i = -1;
		full = 0;
		while (++i < table->philo_nbr)
		{
			check_dead(&table->philos[i]);
			pthread_mutex_lock(&table->philos[i].meal_lock);
			if (table->philos[i].full)
				full++;
			pthread_mutex_unlock(&table->philos[i].meal_lock);
		}
		if (full == table->philo_nbr)
			return (update_end(table),
				write(1, "All Philos have eaten, ending dinner.\n", 39), NULL);
		precise_usleep(1);
	}
	return (NULL);
}

int	check_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->lock);
	end = table->end;
	pthread_mutex_unlock(&table->lock);
	return (end);
}

static void	update_end(t_table *table)
{
	pthread_mutex_lock(&table->lock);
	table->end = 1;
	pthread_mutex_unlock(&table->lock);
}

static void	check_dead(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (check_end(philo->table) == 1)
		return ;
	if (last_meal >= philo->table->time_die && philo->full == 0)
		return (update_end(philo->table), print_routine(philo, 4));
}
