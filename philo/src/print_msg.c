/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:00:19 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/14 01:20:56 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static const char	*get_state_color(t_state state)
{
	if (state == EATING)
		return (EATING_COLOR);
	else if (state == SLEEPING)
		return (SLEEPING_COLOR);
	else if (state == THINKING)
		return (THINKING_COLOR);
	else if (state == DEAD)
		return (DEAD_COLOR);
	return (RESET_COLOR);
}

static const char	*get_state_string(t_state state)
{
	if (state == EATING)
		return ("eating");
	else if (state == SLEEPING)
		return ("sleeping");
	else if (state == THINKING)
		return ("thinking");
	else if (state == DEAD)
		return ("died");
	return ("unknown");
}

void	ft_print_error(const char *message)
{
	if (message)
		printf("%s%s\n", ERROR_MSG_COLOR, message);
}

void	ft_print_state(t_game *game, t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(&game->state_mutex);
	if (!game->simulation_ended)
	{
		current_time = (get_current_time() - game->start_time);
		printf("%s %zu %u %s %s\n", get_state_color(philo->state), current_time,
			philo->id, get_state_string(philo->state), RESET_COLOR);
		if (philo->state == DEAD)
			game->simulation_ended = true;
	}
	pthread_mutex_unlock(&game->state_mutex);
}
