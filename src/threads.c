/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/04/15 22:08:09 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_threads(t_philo **philos, t_params *params)
{
	int	current;

	params->start_time = get_timestamp();
    current = 0;
    while(current < params->num)
    {
        if(pthread_create(&((*philos)[current].thread), NULL, philo_life, &((*philos)[current])))
            return (0);
        current ++;
    }
}
