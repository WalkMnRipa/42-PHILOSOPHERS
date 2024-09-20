/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:36 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/20 19:43:13 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_thinking(t_game *game, t_philo *philo)
{
	philo->state = THINKING;
	ft_print_state(game, philo, MSG_IS_THINKING);
}

void	ft_sleeping(t_game *game, t_philo *philo)
{
	philo->state = SLEEPING;
	ft_print_state(game, philo, MSG_IS_SLEEPING);
	ft_usleep(game->args.t_sleep);
}

static void	update_philo_eating_state(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->meal_lock);
	philo->last_meal = get_current_time();
	if (game->args.nb_eat == -1 || philo->meals_eaten < game->args.nb_eat)
	{
		philo->meals_eaten++;
		philo->state = EATING;
		ft_print_state(game, philo, MSG_IS_EATING);
		pthread_mutex_lock(&game->turn_mutex);
		game->current_turn++;
		pthread_mutex_unlock(&game->turn_mutex);
	}
	pthread_mutex_unlock(&game->meal_lock);
}

static void	check_simulation_end(t_game *game, t_philo *philo)
{
	if (game->args.nb_eat != -1 && philo->meals_eaten >= game->args.nb_eat)
	{
		pthread_mutex_lock(&game->state_mutex);
		game->philos_finished++;
		if (game->philos_finished == game->args.nb_philo)
			game->simulation_ended = true;
		pthread_mutex_unlock(&game->state_mutex);
	}
}

void	ft_eating(t_game *game, t_philo *philo)
{
	take_forks(game, philo);
	pthread_mutex_lock(&game->state_mutex);
	if (game->simulation_ended)
	{
		pthread_mutex_unlock(&game->state_mutex);
		drop_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&game->state_mutex);
	update_philo_eating_state(game, philo);
	ft_usleep(game->args.t_eat);
	drop_forks(philo);
	check_simulation_end(game, philo);
}
