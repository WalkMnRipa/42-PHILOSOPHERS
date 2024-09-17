/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:36 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/17 17:37:07 by jcohen           ###   ########.fr       */
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
	pthread_mutex_lock(philo->right_fork);
	philo->state = FORK;
	ft_print_state(game, philo, MSG_FORK);
	if (game->args.nb_philo == 1)
	{
		ft_usleep(game->args.t_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	philo->state = FORK;
	ft_print_state(game, philo, MSG_FORK);
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
	philo->eat_count++;
	pthread_mutex_unlock(&game->meal_lock);
	philo->state = EATING;
	ft_print_state(game, philo, MSG_IS_EATING);
	ft_usleep(game->args.t_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
