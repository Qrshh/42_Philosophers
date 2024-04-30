/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:44:59 by qrshh             #+#    #+#             */
/*   Updated: 2024/04/29 17:47:35 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void take_fork(char fork_name, t_philo *phil)
{
    int *taken; 
    /* *taken car chaque philo accede a la meme variable
        et permet que chaque philo ne puisse pas determiner
        chacun si la fourchette est prise puisque c'est une 
        ressource commune*/
    t_fork *fork;

    if(!is_dead(phil))
    {
        taken = &(phil->r_taken);
        fork = phil->r_fork;
        if(fork_name == 'l')
        {
            taken = &(phil->l_taken);
            fork = phil->l_fork;
        }
        pthread_mutex_lock(&(fork->lock));
        if(!taken && !fork->used)
        {
            *taken = 1;
            fork->used = 1;
            pthread_mutex_unlock(&(fork->lock));
            write_state("has taken a fork", phil);
        }
        else 
            pthread_mutex_unlock(&(fork->lock));
    }
}

void release_fork(char fork_name, t_philo *phil)
{
    int *taken;

    t_fork *fork;

    taken = &(phil->r_taken);
    fork = phil->r_fork;
    if(fork_name == 'l')
    {
        taken = &(phil->l_taken);
        fork = phil->l_fork;
    }
    pthread_mutex_lock(&(fork->lock));
    *taken = 0;
    fork->used = 0;
    pthread_mutex_unlock(&(fork->lock));
}

void release_fork_and_sleep(t_philo *phil)
{
    release_fork('l', phil);
    release_fork('r', phil);
    write_state("is sleeping", phil);
    ft_usleep(phil->param->time_to_sleep);
}
