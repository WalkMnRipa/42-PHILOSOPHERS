/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/14 00:06:50 by jcohen           ###   ########.fr       */
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
# define DEAD_COLOR "\033[1;31m"
# define EATING_COLOR "\033[1;32m"
# define SLEEPING_COLOR "\033[1;33m"
# define THINKING_COLOR "\033[1;34m"
# define RESET_COLOR "\033[0m"
# define ATE_ENOUGH_COLOR "\033[1;35m"
# define ERROR_MESSAGE_COLOR "\033[1;31m"

// ERRORS
# define ERROR_ARGS_MESSAGE "Usage: ./philo nb_philo t_die t_eat t_sleep [nb_eat_needed]"
# define ERROR_INIT_MESSAGE "Initialize game failed"
# define ERROR_THREAD_MESSAGE "Thread creation failed"
# define ERROR_JOIN_MESSAGE "Thread join failed"
# define ERROR_MUTEX_MESSAGE "Mutex initialization failed"
# define ERROR_MALLOC_MESSAGE "Memory allocation failed"
# define ERROR_SIMULATION_MESSAGE "Simulation failed"

# define MIN_NB_PHILOSOPHERS 2
# define MAX_NB_PHILOSOPHERS 200

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
	ERROR_THREAD_CREATE,
	ERROR_THREAD_JOIN
}					t_error;
typedef struct s_args
{
	unsigned int	nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat_needed;
}					t_args;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_state			state;
	size_t			last_meal;
	int				meals_eaten;
	struct s_game	*game;
}					t_philo;

typedef struct s_game
{
	size_t			start_time;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	state_mutex;
	t_args			args;
	bool			simulation_ended;

}					t_game;

/**************INIT**************/
t_error				ft_init_game(t_game *game, int ac, char **av);

/**************UTILS**************/
void				ft_print_error(const char *message);
void				ft_print_state(t_game *game, t_philo *philo);

int					ft_atoi(const char *str);
int					is_digit(char c);
int					is_valid_arg(char *str);

/**************TIME**************/
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);

/**************LOGGER**************/
void				ft_think(t_game *game, t_philo *philo);
void				ft_sleeping(t_game *game, t_philo *philo);
void				ft_eating(t_game *game, t_philo *philo);

/**************PHILO**************/
void				*ft_check_death(void *arg);
void				*check_meal_count(void *arg);
void				*ft_philo_loop(void *arg);
t_error				ft_run_simulation(t_game *game);

/**************CLEANUP**************/
void				ft_cleanup(t_game *game);
t_error				ft_handle_error(t_game *game, t_error error,
						const char *msg);
void				ft_destroy_mutexes(t_game *game);

#endif
