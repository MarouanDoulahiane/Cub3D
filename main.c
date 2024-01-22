/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:51:18 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/22 21:09:44 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	ft_putstr(char *str, int fd)
{
	if (!str)
	{
		ft_putstr("Error: ft_putstr(NULL)\n", 2);
		exit(1);
	}
	while (*str)
		write(fd, str++, 1);
}

void	print_and_exit(char *msg)
{
	ft_putstr(msg, 2);
	exit(1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		print_and_exit("ErrorUsage: ./cub3D <map.cub>\n");
	parsing(&data, av[1]);
}
