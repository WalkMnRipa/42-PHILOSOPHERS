/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:48 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/12 19:23:15 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_game(t_game *game)
{
	printf("Nb_philo: %d\n", game->nb_philo);
	printf("Time to die: %d\n", game->args.t_die);
	printf("Time to eat: %d\n", game->args.t_eat);
	printf("Time to sleep: %d\n", game->args.t_sleep);
	printf("Nb eat needed: %d\n", game->args.nb_eat_needed);
}

int	main(int ac, char **av)
{
	t_philo	*game;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: %s [nbphi] [t_die] [t_eat] [t_sleep] [option]\n ",
			av[0]);
		return (1);
	}
	ft_init_game(&game, ac, av);
	ft_print_game(&game);
	return (0);
}
