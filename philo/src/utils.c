/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:31 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/13 23:03:00 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_error(const char *message)
{
	if (message)
		printf("%sError: %s\n", ERROR_MESSAGE_COLOR, message);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

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
void	ft_print_state(t_game *game, t_philo *philo)
{
	size_t		current_time;
	const char	*state;
	const char	*color;

	pthread_mutex_lock(&game->state_mutex);
	if (!game->simulation_ended)
	{
		current_time = get_current_time() - game->start_time;
		state = get_state_string(philo->state);
		color = get_state_color(philo->state);
		printf("%s %zu %u %s %s\n", color, current_time, philo->id, state,
			RESET_COLOR);
		if (philo->state == DEAD)
			game->simulation_ended = true;
	}
	pthread_mutex_unlock(&game->state_mutex);
}
