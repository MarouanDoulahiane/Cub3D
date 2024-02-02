/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:33:03 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/02 00:25:48 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	print_env(t_env e)
{
	int	i;

	i = 0;
	printf("%sno: %s\n", GREEN, e.no);
	printf("%sso: %s\n", GREEN, e.so);
	printf("%swe: %s\n", GREEN, e.we);
	printf("%sea: %s\n", GREEN, e.ea);
	printf("%sfloor: %d\n", GREEN, e.floor);
	printf("%sceiling: %d\n", GREEN, e.ceiling);
	printf("%smap:\n", GREEN);
	while (e.map[i])
	{
		printf("%s|%s|\n", GREEN, e.map[i]);
		i++;
	}
	printf("player position: %d, %d\n", e.x, e.y);
}

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_env	e;

	atexit(leaks);
	if (ac != 2)
	{
		printf("%sError: usage ./cub3d <filename>\n%s", RED, RESET);
		exit(1);
	}
	parse_file(av[1], &e);
	rendering(&e);
	print_env(e);
}
