/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 19:00:30 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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

# define MIN_NB_PHILOSOPHERS 2
# define MIN_TIME_TO_DIE 60
# define MIN_TIME_TO_EAT 10
# define MIN_TIME_TO_SLEEP 10

typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}					t_state;

typedef enum s_error
{
	SUCCESS = 0,
	ERROR_ARGS,
	ERROR_MALLOC,
	ERROR_MUTEX_INIT,
	ERROR_THREAD_CREATE
}					t_error;
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
	t_state			state;
	long long		last_meal;
	int				meals_eaten;
}					t_philo;

typedef struct s_game
{
	unsigned int	nb_philo;
	t_args			args;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state_mutex;
	bool			state_mutex_initialized;
	bool			simulation_ended;

}					t_game;

/**************INIT**************/
t_error				ft_init_game(t_game *game, int ac, char **av);

/**************UTILS**************/
void				ft_print_error(const char *message);
long long			get_time_in_ms(void);
int					ft_atoi(const char *str);

/**************CLEANUP**************/
void				ft_cleanup(t_game *game);
t_error				ft_handle_error(t_game *game, t_error error,
						const char *msg);
void				ft_destroy_mutexes(t_game *game);

#endif