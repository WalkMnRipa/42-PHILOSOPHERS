/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:36 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/14 00:23:10 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_think(t_game *game, t_philo *philo)
{
	philo->state = THINKING;
	ft_print_state(game, philo);
}

void	ft_sleeping(t_game *game, t_philo *philo)
{
	philo->state = SLEEPING;
	ft_print_state(game, philo);
	ft_usleep(game->args.t_sleep);
}

void	ft_eating(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_state(game, philo);
	pthread_mutex_lock(philo->left_fork);
	ft_print_state(game, philo);
	philo->state = EATING;
	ft_print_state(game, philo);
	pthread_mutex_lock(&game->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&game->meal_lock);
	ft_usleep(game->args.t_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
