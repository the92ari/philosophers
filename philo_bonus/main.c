/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:57:22 by wwan-taj          #+#    #+#             */
/*   Updated: 2022/04/23 20:05:50 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	int	i;

	i = 0;
	// while (philo->life->death == 0)
	while (i < 1)
	{
		sem_wait(philo->life->lock);
		philo_think(philo);
		philo_takefork(philo);
		philo_takefork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		sem_post(philo->life->lock);
		i++;
	}
}

void	set_philo(t_life *life, int i)
{
	life->philos[i].died = 0;
	life->philos[i].eaten = 0;
	life->philos[i].eating = 0;
	life->philos[i].id = i;
	life->philos[i].life = life;
	life->forkid = life->forks[i];
}

void	create_processes(t_life *life)
{
	int	i;
	int	pid;

	i = 0;
	while (i < life->philo_num)
	{
		pid = fork();
		if (pid == 0)
		{
			set_philo(life, i);
			routine(&life->philos[i]);
		}
		i++;
	}
}

void	set_structs(t_life *life, int ac, char **av)
{
	life->philo_num = ft_atoi(av[1]);
	createforks(life);
	life->philos = malloc(sizeof(t_philo) * life->philo_num);
	life->time_to_die = ft_atoi(av[2]);
	life->time_to_eat = ft_atoi(av[3]);
	life->time_to_sleep = ft_atoi(av[4]);
	life->eat_num = -1;
	life->death = 0;
	if (ac == 6)
		life->eat_num = ft_atoi(av[5]);
}

sem_t	*createforks(t_life *life)
{
	int		i;
	char	*str;
	char	*name;

	str = "fork";
	i = 0;
	while (i < life->philo_num)
	{
		name = ft_strjoin(str, ft_itoa(i));
		life->locks[i] = sem_open(name, O_CREAT, 0644, 1);
		free(name);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_life	life;
	if (ac == 5 || ac == 6)
	{
		set_structs(&life, ac, av);
		create_processes(&life);
		sem_close(life.lock);
		free(life.philos);
	}
	return (0);
}