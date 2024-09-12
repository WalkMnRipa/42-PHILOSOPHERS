/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/12 17:46:41 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NC "\033[0m"
# define BLACK "\033[0;30m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BYELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"


typedef struct s_args
{
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat_needed;
}					t_args;

typedef struct s_philo
{
	unsigned int	id;
	int				nb_forks_taken;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			args;
	bool			is_dead;
	bool			is_eating;
	bool			is_sleeping;
}					t_philo;

typedef struct s_game
{
	int				nb_philo;
	t_philo			*philosophers;
}					t_game;

#endif