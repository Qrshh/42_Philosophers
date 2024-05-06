/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:53 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/02 15:12:26 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_life(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	if (phil->pos % 2 == 0)
		ft_usleep(phil->param->time_to_eat);
	while (!is_dead(phil))
	{
		if (phil->meal_count >= phil->param->meal_max
			&& phil->param->meal_max > 0)
			break ;
		take_fork('l', phil);
		if (phil->l_taken)
			take_fork('r', phil);
		if (phil->l_taken && phil->r_taken)
		{
			write_state("is eating", phil);
			ft_usleep(phil->param->time_to_eat);
			phil->meal_count++;
			pthread_mutex_lock(&(phil->meal_lock));
			phil->last_meal = get_timestamp() - phil->param->start_time;
			pthread_mutex_unlock(&(phil->meal_lock));
			release_fork_and_sleep(phil);
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_params	params;
	t_philo		*philos;
	t_fork		*forks;

	if (!init_params(&params, ac, av))
		exit_error("Wrong set of params");
	if (!create_philos(&philos, &forks, &params))
		exit_error("An error occured while creating philosophers");
	if (!create_threads(&philos, &params))
		exit_error("An error occurred while creating the threads");
	if (!wait_threads(&philos, &params))
		exit_error("Ca marche po");
	return (0);
}
