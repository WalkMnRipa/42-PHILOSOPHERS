/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:40:09 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/20 19:40:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_game *game, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	unsigned int	current_turn;

	pthread_mutex_lock(&game->state_mutex);
	current_turn = game->current_turn;
	pthread_mutex_unlock(&game->state_mutex);
	if (philo->id == ((current_turn % game->args.nb_philo) + 1))
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	philo->state = FORK;
	ft_print_state(game, philo, MSG_FORK);
	pthread_mutex_lock(second_fork);
	ft_print_state(game, philo, MSG_FORK);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
