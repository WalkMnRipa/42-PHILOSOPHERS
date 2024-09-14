/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:27 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/14 02:16:02 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_check_death(void *arg)
{
	t_game			*game;
	size_t			current_time;
	unsigned int	i;

	game = (t_game *)arg;
	while (!game->simulation_ended)
	{
		i = 0;
		while (i < game->args.nb_philo)
		{
			pthread_mutex_lock(&game->meal_lock);
			current_time = get_current_time();
			if (current_time
				- game->philosophers[i].last_meal > (size_t)game->args.t_die)
				return (game->philosophers[i].state = DEAD, ft_print_state(game,
						&game->philosophers[i]), game->simulation_ended = true,
					pthread_mutex_unlock(&game->meal_lock), NULL);
			pthread_mutex_unlock(&game->meal_lock);
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}

void	*check_meal_count(void *arg)
{
	t_game			*game;
	bool			ate_enough;
	unsigned int	i;

	game = (t_game *)arg;
	while (!game->simulation_ended && game->args.nb_eat_needed != -1)
	{
		ate_enough = true;
		pthread_mutex_lock(&game->meal_lock);
		i = 0;
		while (i < game->args.nb_philo && ate_enough)
		{
			if (game->philosophers[i].meals_eaten < game->args.nb_eat_needed)
				ate_enough = false;
			i++;
		}
		pthread_mutex_unlock(&game->meal_lock);
		if (ate_enough)
			return (pthread_mutex_lock(&game->state_mutex),
				game->simulation_ended = true,
				pthread_mutex_unlock(&game->state_mutex), NULL);
		usleep(1000);
	}
	return (NULL);
}

void	*ft_philo_loop(void *arg)
{
	t_philo	*philo;
	t_game	*game;

	philo = (t_philo *)arg;
	game = philo->game;
	while (!game->simulation_ended)
	{
		ft_thinking(game, philo);
		ft_eating(game, philo);
		ft_sleeping(game, philo);
	}
	return (NULL);
}

t_error	ft_run_simulation(t_game *game)
{
	unsigned int	i;

	i = 0;
	game->start_time = get_current_time();
	while (i < game->args.nb_philo)
	{
		if (pthread_create(&game->philosophers[i].thread, NULL, &ft_philo_loop,
				&game->philosophers[i]))
			return (ERROR_THREAD_CREATE);
		i++;
	}
	if (pthread_create(&game->philosophers[0].thread, NULL, &ft_check_death,
			game))
		return (ERROR_THREAD_CREATE);
	if (pthread_create(&game->philosophers[0].thread, NULL, &check_meal_count,
			game))
		return (ERROR_THREAD_CREATE);
	i = 0;
	while (i < game->args.nb_philo)
	{
		if (pthread_join(game->philosophers[i].thread, NULL))
			return (ERROR_THREAD_JOIN);
		i++;
	}
	return (SUCCESS);
}
