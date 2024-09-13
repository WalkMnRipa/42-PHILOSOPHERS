/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:30:44 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 22:30:56 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy_mutexes(t_game *game)
{
	unsigned int	i;

	if (game && game->forks)
	{
		i = 0;
		while (i < game->args.nb_philo)
		{
			pthread_mutex_destroy(&game->forks[i]);
			i++;
		}
		free(game->forks);
		game->forks = NULL;
	}
	pthread_mutex_destroy(&game->state_mutex);
	pthread_mutex_destroy(&game->meal_lock);
}

void	ft_cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->philosophers)
	{
		free(game->philosophers);
		game->philosophers = NULL;
	}
	ft_destroy_mutexes(game);
}

t_error	ft_handle_error(t_game *game, t_error error, const char *msg)
{
	if (msg)
		ft_print_error(msg);
	if (game)
		ft_cleanup(game);
	return (error);
}
