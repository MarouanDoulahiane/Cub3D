/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:57:49 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/04 16:58:00 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

double	get_angle(char c)
{
	double	angle;

	if (c == 'E')
		angle = 0;
	else if (c == 'N')
		angle = 3 * M_PI / 2;
	else if (c == 'W')
		angle = M_PI;
	else
		angle = M_PI / 2;
	return (angle);
}

void	parse_map_is_valid(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (e->map[++i])
	{
		j = -1;
		if (is_white_space(e->map[i]))
			print_error("invalid file");
		while (e->map[i][++j])
		{
			if (!is_valid_map_char(e->map[i][j]))
				print_error("invalid file");
			if (is_player(e->map[i][j]))
			{
				if (e->x != -1 || e->y != -1)
					print_error("invalid file");
				e->x = j * SIZE + SIZE / 2;
				e->y = i * SIZE + SIZE / 2;
				e->angle = get_angle(e->map[i][j]);
			}
		}
	}
	if (e->x == -1 || e->y == -1)
		print_error("invalid file");
}

bool	is_not_wall(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == '0');
}

void	parse_map_is_closed(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	while (e->map[i])
	{
		j = 0;
		while (e->map[i][j])
		{
			if (is_not_wall(e->map[i][j]))
			{
				if (i == 0 || j == 0 || !e->map[i + 1] || !e->map[i][j + 1])
					print_error("invalid file");
				if (e->map[i - 1][j] == ' ' || e->map[i][j - 1] == ' '
					|| e->map[i + 1][j] == ' ' || e->map[i][j + 1] == ' ')
					print_error("invalid file");
			}
			j++;
		}
		i++;
	}
}
