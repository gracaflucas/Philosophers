/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:19:19 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 13:19:20 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_fork
{
	int				id;
	pthread_mutex_t	fork;	
}					t_fork;

typedef struct	s_philo
{
	int						id;
	int						meals;
	int						full;
	long					last_meal_time;
	t_fork					*left;
	t_fork					*right;
	pthread_t				thread_id;
	typedef struct s_table	*table;
}							t_philo;

typedef struct s_table
{
	t_philo	*philos;
	t_fork	*forks;
	int		time_eat;
	int		time_sleep;
	int		time_think;
	int		max_meals;
	long	start;
	int		end;
}			t_table;

void	*monitor();

int		parsing(char **argv, int argc);

#endif
