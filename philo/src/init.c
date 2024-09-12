/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:34 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/12 19:13:11 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_init_nb_philos(int nb_philo)
{
	void	*philosophers;

	if (nb_philo < 2)
		ft_clean_philo_print_error_and_exit(NULL,
			"Error: Nb_philosophers must be >= 2");
	philosophers = malloc(sizeof(t_philo) * nb_philo);
	if (!philosophers)
		ft_clean_philo_print_error_and_exit(NULL, "Error: malloc philosophers");
	return (philosophers);
}

void	ft_init_forks(t_game *game)
{
	unsigned int	i;

	game->forks = malloc(sizeof(pthread_mutex_t) * game->nb_philo);
	if (!game->forks)
		ft_clean_philo_print_error_and_exit(game, "Error: malloc forks");
	i = 0;
	while (i < game->nb_philo)
	{
		if (pthread_mutex_init(&game->forks[i], NULL) != 0)
			ft_clean_philo_print_error_and_exit(game, "Error: mutex init");
		i++;
	}
}

void	ft_check_and_set_values(t_game *game, int ac, char **av)
{
	game->args.t_die = ft_atoi(av[2]);
	game->args.t_eat = ft_atoi(av[3]);
	game->args.t_sleep = ft_atoi(av[4]);
	if (game->args.t_die < MIN_TIME_TO_DIE || game->args.t_eat < MIN_TIME_TO_EAT
		|| game->args.t_sleep < MIN_TIME_TO_SLEEP)
		ft_clean_philo_print_error_and_exit(game, "Error: Time must be >= 60");
	if (ac == 6)
		game->args.nb_eat_needed = ft_atoi(av[5]);
	else
		game->args.nb_eat_needed = -1;
}

void	ft_init_philosophers(t_game *game)
{
	unsigned int	i;

	i = 0;
	while (i < game->nb_philo)
	{
		game->philosophers[i].id = i + 1;
		game->philosophers[i].nb_forks_taken = 1;
		game->philosophers[i].is_dead = false;
		game->philosophers[i].is_eating = false;
		game->philosophers[i].is_sleeping = false;
		i++;
	}
}

void	ft_init_game(t_game *game, int ac, char **av)
{
	game->nb_philo = ft_atoi(av[1]);
	game->philosophers = ft_init_nb_philos(game->nb_philo);
	ft_init_forks(game);
	ft_check_and_set_values(game, ac, av);
	ft_init_philosophers(game);
	game->someone_died = false;
}
