/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:48 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 22:48:48 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_game(t_game *game)
{
	int	i;

	i = 0;
	printf("CURRENT TIME = %zu ms \n", get_current_time() - game->start_time);
	printf("Number of philosophers: %d\n", game->args.nb_philo);
	printf("Time to die: %d\n", game->args.t_die);
	printf("Time to eat: %d\n", game->args.t_eat);
	printf("Time to sleep: %d\n", game->args.t_sleep);
	printf("Number of times each philosopher must eat: %d\n",
		game->args.nb_eat_needed);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_error	error;

	if (ac < 5 || ac > 6)
		return (ft_print_error(ERROR_ARGS_MESSAGE), ERROR_ARGS);
	error = ft_init_game(&game, ac, av);
	if (error != SUCCESS)
		return (ft_handle_error(&game, error, ERROR_INIT_MESSAGE));
	error = ft_run_simulation(&game);
	if (error != SUCCESS)
		return (ft_handle_error(&game, error, ERROR_SIMULATION_MESSAGE));
	ft_cleanup(&game);
	return (SUCCESS);
}
