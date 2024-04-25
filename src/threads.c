/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/04/25 16:27:14 by qrshh            ###   ########.fr       */
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
    if (pthread_create(&(params->death_thread), NULL, check_philos_death, philos))
        return (0);
    //creer un thread pour check la mort DONE
    return (1);
}
