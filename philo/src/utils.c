/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:31 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/12 18:56:00 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_clean_print_error_and_exit(t_game *game, const char *message)
{
	if (game)
	{
		if (game->philosophers)
		{
			free(game->philosophers);
			game->philosophers = NULL;
		}
		if (game->forks)
		{
			free(game->forks);
			game->forks = NULL;
		}
	}
	printf("%s\n", message);
	exit(1);
}
