/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:30 by tumolabs          #+#    #+#             */
/*   Updated: 2024/01/06 17:10:51 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing1(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argc < 5 || argc > 6
				|| !(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("ERROR: Invalid arguments!");
				return (1);
			}
		}
		if (ft_strlen(argv[i]) >= 10
			&& ft_strncmp(argv[i], "2147483647", 10))
		{
			printf("ERROR: Too big arguments!");
			return (1);
		}
	}
	return (0);
}

int	parsing2(t_data *data, int argc, char **argv)
{
	if (!data->info->nb_of_philos)
		return (1);
	if (argc == 6)
	{
		if (!ft_atoi(argv[5]))
			return (1);
	}
	if (data->info->die_time < 61 || data->info->eat_time < 61
		|| data->info->sleep_time < 61)
		return (1);
	return (0);
}

void	clear_data(t_data **data)
{
	int	i;

	i = -1;
	while (++i < (*data)->info->nb_of_philos)
	{
		pthread_mutex_destroy(&(*data)->info->fork[i]);
		pthread_mutex_destroy(&(*data)->info->meals[i]);
	}
	pthread_mutex_destroy(&(*data)->info->print);
	pthread_mutex_destroy(&(*data)->info->time);
	pthread_mutex_destroy(&(*data)->info->die);
}

int	init_data(t_data **data)
{
	if (init_mutexes(data))
		return (1);
	if (create_threads(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!parsing1(argc, argv))
	{
		if (init_args(argc, argv, &data))
			return (1);
		if (init_data(&data))
		{
			clear_data(&data);
			return (1);
		}
	}
	else
		return (1);
	return (0);
}
