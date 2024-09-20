/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:27 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/20 18:36:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_check_meals(t_game *game)
{
	unsigned int	i;
	bool			all_ate_enough;

	if (game->args.nb_eat == -1)
		return (false);
	pthread_mutex_lock(&game->meal_lock);
	all_ate_enough = true;
	i = 0;
	while (i < game->args.nb_philo)
	{
		if (game->philosophers[i].meals_eaten < game->args.nb_eat)
		{
			all_ate_enough = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&game->meal_lock);
	return (all_ate_enough);
}

bool	ft_check_death(t_game *game)
{
	unsigned int	i;
	size_t			current_time;
	size_t			since_last_meal;

	i = 0;
	while (i < game->args.nb_philo)
	{
		pthread_mutex_lock(&game->meal_lock);
		current_time = get_current_time();
		since_last_meal = current_time - game->philosophers[i].last_meal;
		if (since_last_meal > (size_t)game->args.t_die)
		{
			game->philosophers[i].state = DEAD;
			pthread_mutex_unlock(&game->meal_lock);
			ft_print_state(game, &game->philosophers[i], MSG_DIED);
			pthread_mutex_lock(&game->meal_lock);
			game->simulation_ended = true;
			pthread_mutex_unlock(&game->meal_lock);
			return (true);
		}
		pthread_mutex_unlock(&game->meal_lock);
		i++;
	}
	return (false);
}

void	*ft_philo_loop(void *arg)
{
	t_philo	*philo;
	t_game	*game;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	game = philo->game;
	while (!game->simulation_ended)
	{
		ft_eating(game, philo);
		if (game->simulation_ended)
			break ;
		ft_sleeping(game, philo);
		if (game->simulation_ended)
			break ;
		ft_thinking(game, philo);
	}
	return (NULL);
}

t_error	ft_run_simulation(t_game *game)
{
	unsigned int	i;

	i = -1;
	game->start_time = get_current_time();
	while (++i < game->args.nb_philo)
		if (pthread_create(&game->philosophers[i].thread, NULL, &ft_philo_loop,
				&game->philosophers[i]))
			return (ERROR_THREAD_CREATE);
	while (!game->simulation_ended)
	{
		if (ft_check_death(game) || ft_check_meals(game))
		{
			pthread_mutex_lock(&game->state_mutex);
			game->simulation_ended = true;
			pthread_mutex_unlock(&game->state_mutex);
		}
		usleep(500);
	}
	i = -1;
	while (++i < game->args.nb_philo)
		if (pthread_join(game->philosophers[i].thread, NULL))
			return (ERROR_THREAD_JOIN);
	return (SUCCESS);
}
