/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:48 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/14 02:15:58 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_error	error;

	if (ac < 5 || ac > 6)
		return (ft_print_error(ERROR_ARGS_MSG), ERROR_ARGS);
	error = ft_init_game(&game, ac, av);
	if (error != SUCCESS)
		return (ft_handle_error(&game, error, ERROR_INIT_MSG));
	error = ft_run_simulation(&game);
	if (error != SUCCESS)
		return (ft_handle_error(&game, error, ERROR_SIMULATION_MSG));
	ft_cleanup(&game);
	return (SUCCESS);
}
