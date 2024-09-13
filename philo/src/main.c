/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:48 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 19:08:29 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_game(t_game *game)
{
	long long	start_time;

	start_time = get_time_in_ms();
	printf("%lld ms: Nb_philo: %d\n", get_time_in_ms() - start_time,
		game->nb_philo);
	printf("%lld ms: Time to die: %d\n", get_time_in_ms() - start_time,
		game->args.t_die);
	printf("%lld ms: Time to eat: %d\n", get_time_in_ms() - start_time,
		game->args.t_eat);
	printf("%lld ms: Time to sleep: %d\n", get_time_in_ms() - start_time,
		game->args.t_sleep);
	printf("%lld ms: Nb eat needed: %d\n", get_time_in_ms() - start_time,
		game->args.nb_eat_needed);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_error	error;

	if (ac < 5 || ac > 6)
		return (ft_print_error("Usage: ./philo nb_philo t_die t_eat t_sleep [nb_eat_needed]"),
			ERROR_ARGS);
	error = ft_init_game(&game, ac, av);
	if (error != SUCCESS)
		return (ft_handle_error(&game, error, "Error Initializing game"));
	ft_print_game(&game);
	ft_cleanup(&game);
	return (SUCCESS);
}
