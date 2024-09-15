/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:36 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/15 20:03:02 by jcohen           ###   ########.fr       */
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

void	ft_eating(t_game *game, t_philo *philo)
{
	bool should_continue ;
	pthread_mutex_lock(philo->right_fork);
	ft_print_state(game, philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_print_state(game, philo, "has taken a fork");
	pthread_mutex_lock(&game->state_mutex);
	if (game->simulation_ended)
	{
		pthread_mutex_unlock(&game->state_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(&game->state_mutex);
	pthread_mutex_lock(&game->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&game->meal_lock);
	ft_print_state(game, philo, "is eating");
	ft_usleep(game->args.t_eat);
	pthread_mutex_lock(&game->state_mutex);
	should_continue = !game->simulation_ended;
	pthread_mutex_unlock(&game->state_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!should_continue)
		return ;
}
