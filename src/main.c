/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:53 by abesneux          #+#    #+#             */
/*   Updated: 2024/04/16 20:16:06 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_life(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	if (phil->pos % 2 == 0)
		ft_uspleep(phil->param->time_to_eat);
			// faire la fonction usleep qui permet au philo d'attendre jusqu'a manger
	while (!is_dead(phil))                   
		// faire une fonction qui permet de check si le philo n'est pas mort (mutex peut etre ????)
	{
		if (phil->meal_count >= phil->param->meal_max
			&& phil->param->meal_max > 0)
			break ;
	}
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
}
