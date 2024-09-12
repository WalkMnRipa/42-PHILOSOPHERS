/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:48 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/12 17:32:04 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_philo			*game;
	unsigned int	nb_philo;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: %s [nbphi] [t_die] [t_eat] [t_sleep] [option]\n ",
			av[0]);
		return (1);
	}
	ft_init_philo(&game, av);
	ft_free_philo();
	return (0);
}
