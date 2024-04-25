/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:52:48 by qrshh             #+#    #+#             */
/*   Updated: 2024/04/25 16:25:56 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int is_dead(t_philo *phil)
{
    int alive;

    pthread_mutex_lock(&(phil->param->mutex_is_dead));
    alive = phil->param->is_dead;
    pthread_mutex_unlock(&(phil->param->mutex_is_dead));
    return (alive);
}

int check_death(t_philo *phil, long current_time)
{
    int dead;
    int last_meal;

    dead = 0;
    pthread_mutex_lock (&(phil->meal_lock));
    last_meal = current_time - phil->last_meal;
    pthread_mutex_unlock(&(phil->meal_lock));
    if(last_meal > phil->param->time_to_die)
    {
        pthread_mutex_lock(&(phil->param->mutex_is_dead));
        phil->param->is_dead = 1;
        pthread_mutex_unlock(&(phil->param->mutex_is_dead));
        write_state("Died", phil);
        dead = 1;
    }
    return (dead);
}

void *check_philos_death(void *arg)
{
    t_params *params;
    t_philo **philos;
    long current_time;
    int current;

    philos = (t_philo **)arg;
    params = philos[0]->param;
    while(1)
    {
        current = 0;
        current_time = get_timestamp() - params->start_time;
        while(current > params->num)
        {
            if(check_death(&(*philos)[current], current_time))
                return (NULL);
            current ++;
        }
        ft_usleep(1);
    }
    return (NULL);
}