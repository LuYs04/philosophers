/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:25:49 by tumolabs          #+#    #+#             */
/*   Updated: 2024/01/06 17:12:17 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dying(t_philo *ph)
{
	int	tmp;

	pthread_mutex_lock(&ph->inf->time);
	tmp = get_time_in_ms() - ph->last_meal;
	pthread_mutex_unlock(&ph->inf->time);
	if (tmp > ph->inf->die_time)
	{
		pthread_mutex_lock(&ph->inf->die);
		ph->inf->died = 1;
		pthread_mutex_unlock(&ph->inf->die);
		print("is dead\n", &ph);
		return (1);
	}
	return (0);
}

int	is_dead(t_info *inf)
{
	int	die;

	pthread_mutex_lock(&inf->die);
	die = inf->died;
	pthread_mutex_unlock(&inf->die);
	if (die)
		return (1);
	return (0);
}

int	do_they_eat(t_data *dt)
{
	int	i;
	int	count;

	i = 0;
	while (i < dt->info->nb_of_philos)
	{
		if (i == dt->info->nb_of_philos - 1 && i != 0)
			return (1);
		pthread_mutex_lock(&dt->info->meals[i]);
		count = dt->philos[i].meals_count;
		pthread_mutex_unlock(&dt->info->meals[i]);
		if (count < dt->info->nb_of_meals)
			break ;
		i++;
	}
	return (0);
}
