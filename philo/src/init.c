/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:34 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 22:50:20 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_error	ft_parse_args(t_game *game, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ERROR_ARGS);
	game->args.nb_philo = ft_atoi(av[1]);
	game->args.t_die = ft_atoi(av[2]);
	game->args.t_eat = ft_atoi(av[3]);
	game->args.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		game->args.nb_eat_needed = ft_atoi(av[5]);
	else
		game->args.nb_eat_needed = -1;
	if (game->args.nb_philo < MIN_NB_PHILOSOPHERS
		|| game->args.nb_philo > MAX_NB_PHILOSOPHERS || (ac == 6
			&& game->args.nb_eat_needed <= 0))
		return (ERROR_ARGS);
	return (SUCCESS);
}

static t_error	ft_init_mutexes(t_game *game)
{
	unsigned int	i;

	game->forks = malloc(sizeof(pthread_mutex_t) * game->args.nb_philo);
	if (!game->forks)
		return (ERROR_MALLOC);
	i = 0;
	while (i < game->args.nb_philo)
	{
		if (pthread_mutex_init(&game->forks[i], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&game->forks[--i]);
			free(game->forks);
			game->forks = NULL;
			return (ERROR_MUTEX_INIT);
		}
		i++;
	}
	if (pthread_mutex_init(&game->state_mutex, NULL)
		|| pthread_mutex_init(&game->meal_lock, NULL))
	{
		ft_destroy_mutexes(game);
		return (ERROR_MUTEX_INIT);
	}
	return (SUCCESS);
}

static t_error	ft_init_philosophers(t_game *game)
{
	unsigned int	i;

	game->philosophers = malloc(sizeof(t_philo) * game->args.nb_philo);
	if (!game->philosophers)
		return (ERROR_MALLOC);
	i = 0;
	while (i < game->args.nb_philo)
	{
		game->philosophers[i].id = i + 1;
		game->philosophers[i].state = THINKING;
		game->philosophers[i].last_meal = get_current_time();
		game->philosophers[i].meals_eaten = 0;
		game->philosophers[i].left_fork = &game->forks[i];
		game->philosophers[i].right_fork = &game->forks[(i + 1)
			% game->args.nb_philo];
		game->philosophers[i].game = game;
		i++;
	}
	return (SUCCESS);
}

t_error	ft_init_game(t_game *game, int ac, char **av)
{
	t_error	error;

	memset(game, 0, sizeof(t_game));
	error = ft_parse_args(game, ac, av);
	if (error != SUCCESS)
		return (error);
	error = ft_init_mutexes(game);
	if (error != SUCCESS)
		return (error);
	error = ft_init_philosophers(game);
	if (error != SUCCESS)
	{
		ft_destroy_mutexes(game);
		return (error);
	}
	game->simulation_ended = false;
	game->start_time = get_current_time();
	return (SUCCESS);
}
