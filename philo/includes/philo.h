/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/16 19:39:12 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD_COLOR "\033[1;31m"
# define EATING_COLOR "\033[1;32m"
# define FORK_COLOR "\033[1;36m"
# define SLEEPING_COLOR "\033[1;33m"
# define THINKING_COLOR "\033[1;34m"
# define RESET_COLOR "\033[0m"
# define ATE_ENOUGH_COLOR "\033[1;35m"
# define ERROR_MSG_COLOR "\033[1;31m"

# define ERROR_ARGS_MSG "Usage: ./philo nb_philo t_die t_eat t_sleep [nb_eat]"
# define ERROR_INIT_MSG "Initialize game failed"
# define ERROR_SIMULATION_MSG "Simulation failed"

# define MSG_DIED "died"
# define MSG_IS_EATING "is eating"
# define MSG_IS_SLEEPING "is sleeping"
# define MSG_IS_THINKING "is thinking"
# define MSG_FORK "has taken a fork"

# define MIN_NB_PHILOSOPHERS 2
# define MAX_NB_PHILOSOPHERS 200
# define MIN_T_ARGS 60

typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FORK
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
}					t_args;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_state			state;
	size_t			last_meal;
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
void				ft_print_state(t_game *game, t_philo *philo,
						const char *msg);

int					ft_atoi(const char *str);
int					is_digit(char c);
int					is_valid_arg(char *str);
int					ft_strcmp(const char *s1, const char *s2);

/**************TIME**************/
size_t				get_current_time(void);
void				ft_usleep(size_t milliseconds);

/**************LOGGER**************/
void				take_forks(t_game *game, t_philo *philo);
void				drop_forks(t_philo *philo);
void				ft_thinking(t_game *game, t_philo *philo);
void				ft_sleeping(t_game *game, t_philo *philo);
void				ft_eating(t_game *game, t_philo *philo);

/**************PHILO**************/
bool				ft_check_death(t_game *game);
void				*ft_philo_loop(void *arg);
t_error				ft_run_simulation(t_game *game);

/**************CLEANUP**************/
void				ft_cleanup(t_game *game);
t_error				ft_handle_error(t_game *game, t_error error,
						const char *msg);
void				ft_destroy_mutexes(t_game *game);

#endif
