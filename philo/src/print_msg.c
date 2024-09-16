/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:00:19 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/16 16:36:07 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_error(const char *message)
{
	if (message)
		printf("%s%s\n", ERROR_MSG_COLOR, message);
}

static char	*get_color(t_state state)
{
	if (state == EATING)
		return (EATING_COLOR);
	if (state == SLEEPING)
		return (SLEEPING_COLOR);
	if (state == THINKING)
		return (THINKING_COLOR);
	if (state == DEAD)
		return (DEAD_COLOR);
	return (RESET_COLOR);
}

void	ft_print_state(t_game *game, t_philo *philo, const char *msg)
{
	size_t	current_time;

	pthread_mutex_lock(&game->state_mutex);
	if (!game->simulation_ended)
	{
		current_time = get_current_time() - game->start_time;
		printf("%s %zu %d %s\n", get_color(philo->state), current_time,
			philo->id, msg);
	}
	pthread_mutex_unlock(&game->state_mutex);
}
