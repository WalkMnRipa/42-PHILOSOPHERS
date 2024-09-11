/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/09/11 19:50:51 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NC "\033[0m"
# define BLACK "\033[0;30m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BYELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"
# define TIMES_TO_COUNT 21000

typedef struct s_counter
{
	pthread_mutex_t	counter_mutex;
	unsigned int	count;
}					t_counter;

#endif