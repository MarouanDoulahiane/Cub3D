/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:51:18 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/23 17:15:30 by mdoulahi         ###   ########.fr       */
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

void	f()
{
	system("leaks cub3D");
}

void	free_data(t_info data)
{
	free(data.no);
	free(data.so);
	free(data.we);
	free(data.ea);
	free2d(data.map);
}

void	printData(t_info data)
{
	printf("######### - MAP DATA - #########\n\n");
	printf("NO %s\n", data.no);
	printf("SO %s\n", data.so);
	printf("WE %s\n", data.we);
	printf("EA %s\n", data.ea);
	printf("\n");
	printf("C %d,%d,%d\n", data.c.r, data.c.g, data.c.b);
	printf("F %d,%d,%d\n\n", data.f.r, data.f.g, data.f.b);
	for (int i = 0; data.map[i]; i++)
		printf("|%s|\n", data.map[i]);
	printf("\n################################\n");
}

int	main(int ac, char **av)
{
	t_info	data;

	// atexit(f);

	if (ac != 2)
		print_and_exit("ErrorUsage: ./cub3D <map.cub>\n");
	parsing(&data, av[1]);
	printData(data);
	free_data(data);
}
