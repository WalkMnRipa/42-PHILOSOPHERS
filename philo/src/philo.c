/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:27 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 22:47:27 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_think(philo->game, philo);
		ft_eating(philo->game, philo);
		ft_sleeping(philo->game, philo);
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
		if (pthread_create(&game->philosophers[i].thread, NULL, &ft_philo,
				&game->philosophers[i]))
			return (ERROR_THREAD_CREATE);
		i++;
	}
	i = 0;
	while (i < game->args.nb_philo)
	{
		if (pthread_join(game->philosophers[i].thread, NULL))
			return (ERROR_THREAD_JOIN);
		i++;
	}
	return (SUCCESS);
}
