/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/12 19:14:58 by jcohen           ###   ########.fr       */
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

// COLORS
# define NC "\033[0m"
# define BLACK "\033[0;30m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BYELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"

# define MIN_TIME_TO_DIE 60
# define MIN_TIME_TO_EAT 10
# define MIN_TIME_TO_SLEEP 10

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
	bool			is_dead;
	bool			is_eating;
	bool			is_sleeping;
}					t_philo;

typedef struct s_game
{
	int				nb_philo;
	t_args			args;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	bool			someone_died;

}					t_game;

/**************INIT**************/
void				*ft_init_nb_philos(int nb_philo);
void				ft_init_forks(t_game *game);
void				ft_check_and_set_values(t_game *game, int ac, char **av);
void				ft_init_philosophers(t_game *game);
void				ft_init_game(t_game *game, int ac, char **av);

/**************UTILS**************/
void				ft_clean_print_error_and_exit(t_game *game,
						const char *message);

#endif