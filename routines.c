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

static void	*philo_eat(t_philo *philo);
static void	*philo_think(t_philo *philo);
static void	*philo_sleep(t_philo *philo);

void	*routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->table->max_meals == 0)
        return (NULL);
    if (philo->table->philo_nbr == 1)
    {
        printf("Philosopher %d has only one fork and will starve.\n", philo->id);
        precise_usleep(philo->table->time_die);
        return (NULL);
    }
    while (1)
    {
        pthread_mutex_lock(&philo->table->lock);
        if (philo->table->end)
           return (pthread_mutex_unlock(&philo->table->lock), NULL);
        pthread_mutex_unlock(&philo->table->lock);
        if (!philo->full)
            philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

void    *monitor(void *arg)
{
    t_table *table;
    int     i;
    int     full;
    long    time_since_last_meal;

    table = (t_table *)arg;
    while (1)
    {
        pthread_mutex_lock(&table->lock);
        if (table->end)
            return (pthread_mutex_unlock(&table->lock), NULL);
        pthread_mutex_unlock(&table->lock);
        i = -1;
        full = 0;
        while (++i < table->philo_nbr)
        {
            pthread_mutex_lock(&table->philos[i].meal_lock);
            time_since_last_meal = get_current_time() - table->philos[i].last_meal_time;
            pthread_mutex_unlock(&table->philos[i].meal_lock);
            pthread_mutex_lock(&table->lock);
            if (table->end)
                return (pthread_mutex_unlock(&table->lock), NULL);
            pthread_mutex_unlock(&table->lock);
            if (time_since_last_meal >= table->time_die)
            {
                pthread_mutex_lock(&table->lock);
                table->end = 1;
                pthread_mutex_unlock(&table->lock);
                return (printf("Philosopher %d has died.\n", table->philos[i].id), NULL);
            }
            if (table->philos[i].full)
                full++;
        }
        if (full == table->philo_nbr)
        {
            pthread_mutex_lock(&table->lock);
            table->end = 1;
            pthread_mutex_unlock(&table->lock);
            return (NULL);
        }
    }
    return (NULL);
}

static void	*philo_eat(t_philo *philo)
{
    if (philo->table->end)
        return (NULL);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->left->fork);
        pthread_mutex_lock(&philo->right->fork);
    }
    else
    {
        pthread_mutex_lock(&philo->right->fork);
        pthread_mutex_lock(&philo->left->fork);
    }
    printf("Philosopher %d is eating.\n", philo->id);
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = get_current_time();
    philo->meals += 1;
    if (philo->meals == philo->table->max_meals && philo->table->max_meals != 0)
        philo->full = 1;
    pthread_mutex_unlock(&philo->meal_lock);
    precise_usleep(philo->table->time_eat);
    pthread_mutex_unlock(&philo->left->fork);
    pthread_mutex_unlock(&philo->right->fork);
    return (NULL);
}

static void	*philo_think(t_philo *philo)
{
    if (philo->table->end)
        return (NULL);
    printf("Philosopher %d is thinking.\n", philo->id);
    precise_usleep(100);
    return (NULL);
}

static void	*philo_sleep(t_philo *philo)
{
    if (philo->table->end)
        return (NULL);
    printf("Philosopher %d is sleeping.\n", philo->id);
    precise_usleep(philo->table->time_sleep);
    return (NULL);
}
